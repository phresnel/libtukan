// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef SPECTRUM_HH_INCLUDED_20131017
#define SPECTRUM_HH_INCLUDED_20131017

#include "tuple.hh"
#include "Nanometer.hh"
#include "Interval.hh"
#include <valarray>
#include <stdexcept>

namespace gaudy {

    //----------------------------------------------------------------------------------------------
    // SpectrumSample
    //----------------------------------------------------------------------------------------------
    struct SpectrumSample {
        Nanometer wavelength;
        float     amplitude = 0;

        SpectrumSample() = default;
        SpectrumSample(Nanometer w, float a) : wavelength(w), amplitude(a) {}
    };

    inline bool operator== (SpectrumSample const &lhs, SpectrumSample const &rhs) {
        return lhs.wavelength == rhs.wavelength && lhs.amplitude == rhs.amplitude;
    }
    inline bool operator!= (SpectrumSample const &lhs, SpectrumSample const &rhs) {
        return !(lhs == rhs);
    }

    inline bool rel_equal(SpectrumSample const &lhs, SpectrumSample const &rhs,
                          float max_rel_diff=std::numeric_limits<float>::epsilon())
    {
        return rel_equal(lhs.amplitude, rhs.amplitude, max_rel_diff)
            && rel_equal(lhs.wavelength, rhs.wavelength, max_rel_diff);
    }


    //----------------------------------------------------------------------------------------------
    // Spectrum
    //----------------------------------------------------------------------------------------------
    class Spectrum {
    public:
        template <typename Cont>
        Spectrum (Nanometer lambda_min, Nanometer lambda_max, Cont const &bins)
        : lambda_min_(lambda_min), lambda_max_(lambda_max), bins_(bins.size())
        {
            bins_.resize(bins.size());
            for (size_t i=0; i!=bins.size(); ++i)
                bins_[i] = bins[i];
        }

        Nanometer lambda_min() const { return lambda_min_; }
        Nanometer lambda_max() const { return lambda_max_; }

        size_t size() const { return bins_.size(); }
        bool empty() const { return 0==size(); }

        SpectrumSample  operator[] (size_t i) const noexcept {
            Nanometer f = Nanometer(i) / Nanometer(size()-1);
            f = lambda_min_ + f*(lambda_max_-lambda_min_);
            return SpectrumSample(f, bins_[i]);
        }

        SpectrumSample  at (size_t i) const {
            if (i < std::numeric_limits<size_t>::min() || i>=size())
                throw std::out_of_range("passed value outside range to Spectrum::at(size_t)");
            return (*this)[i];
        }

        SpectrumSample operator() (float f) const {
            if (f<0) throw std::logic_error("passed value < 0 to Spectrum::operator()(float)");
            if (f>1) throw std::logic_error("passed value > 1 to Spectrum::operator()(float)");
            if (f == 0.0) return SpectrumSample(lambda_min(), bins_[0]);
            if (f == 1.0) return SpectrumSample(lambda_max(), bins_[size()-1]);

            Nanometer g = lambda_min_ + Nanometer(f)*(lambda_max_-lambda_min_);
            int i = f*static_cast<float>(size()-1);

            float frac = (f-bin_min(i)) / (bin_min(i+1)-bin_min(i));
            if (size_t(i+1) >= size()) // TODO: can this happen?
                    throw std::logic_error("crap");
            return SpectrumSample(g, bins_[i]*(1-frac) + bins_[i+1]*frac);
        }

        SpectrumSample operator() (Nanometer g) const {
            if (g<lambda_min_) throw std::logic_error("passed value < lambda_min to "
                                                      "Spectrum::operator()(Nanometer)");
            if (g>lambda_max_) throw std::logic_error("passed value > lambda_max to "
                                                      "Spectrum::operator()(Nanometer)");

            float f = static_cast<float>((g - lambda_min_) / (lambda_max_-lambda_min_));
            return (*this)(f);
        }

        SpectrumSample operator() (Interval<float> r) const {
            if (r.min()<0) throw std::logic_error("passed value < 0 to "
                                                  "Spectrum::operator()(Interval<float>)");
            if (r.max()>1) throw std::logic_error("passed value > 1 to "
                                                  "Spectrum::operator()(Interval<float>)");

            if (r.min() == r.max()) {
                // We assume that (amp*0)/inf == amp.
                return (*this)(r.min());
            }

            auto avg = [](Interval<float> const &i, float A, float B)
            {
                return 0.5*(A*(1-i.min()) + B*i.min())
                        + 0.5*(A*(1-i.max()) + B*i.max());
            };

            const auto delta = float(1)/(size()-1);
            auto bin_average = [&delta, &r, &avg, this] (int bin)
            {
                const Interval<float> bin_global (bin*delta, bin*delta+delta);
                const auto overlap_global = intersection(bin_global, r);
                //if (!overlap_global)
                //    throw std::logic_error("in SpectrumSample::operator()(Interval)");

                // translate the spectrum-space overlap-interval to bin-space
                const Interval<float> overlap_local((overlap_global->min()-bin_global.min())/delta,
                                                    (overlap_global->max()-bin_global.min())/delta);

                const auto weight = length(*overlap_global);
                const auto local_avg_amplitude = avg(overlap_local, bins_[bin], bins_[bin+1]);
                return make_tuple(weight, local_avg_amplitude);
            };

            const int min_i = r.min() * (size()-1);
            const int max_i = r.max() * (size()-1);

            float weight_total = 0;
            SpectrumSample ret;

            // Given our bins            [    |    |    |    |    ]
            // with the query interval      [______________]
            // we compute the average and weight for the first and last bin in the interval exactly,
            // and then iterate over the inner bins using a constant weight:
            //  [exact|const|const|exact|    ]
            //     [________________]

            // First bin:
            {
                auto ba = bin_average(min_i);
                ret.amplitude += get<1>(ba) * get<0>(ba);
                weight_total  += get<0>(ba);
            }

            // Second bin (if there's only one bin in the interval, we already have it):
            if (min_i != max_i)
            {
                auto ba = bin_average(max_i);
                ret.amplitude += get<1>(ba) * get<0>(ba);
                weight_total  += get<0>(ba);
            }

            // Inner bins with known weight (we could solely use the bin_average() function,
            //                               but this is less performant)
            for (auto i=min_i+1; i<max_i; ++i) {
                auto ba = bins_[i]*0.5f + bins_[i+1]*0.5f;
                ret.amplitude += ba * delta;
                weight_total  += delta;
            }

            ret.amplitude /= weight_total;
            ret.wavelength = Nanometer(avg(r, float(lambda_min_), float(lambda_max_)));

            return ret;
        }

    private:
        Nanometer lambda_min_, lambda_max_;
        std::valarray<float> bins_;

        float bin_min(int index) const noexcept {
            float f = index / float(size()-1);
            return f;
        }
    };
}

#endif // SPECTRUM_HH_INCLUDED_20131017
