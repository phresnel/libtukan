// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.


#include "gaudy/Nanometer.hh"
#include "gaudy/Interval.hh"
#include "gaudy/rel_equal.hh"

#include <vector>
#include <valarray>
#include <iostream>
#include <stdexcept>
#include <tuple>


namespace gaudy {
    using std::get;
    using std::tuple;
    using std::make_tuple;
}



namespace gaudy {
    //----------------------------------------------------------------------------------------------
    // Spectrum
    // TODO: noexcept, constexpr
    //----------------------------------------------------------------------------------------------
    struct SpectrumSample {
        Nanometer wavelength;
        float     amplitude = 0;

        SpectrumSample() = default;
        SpectrumSample(Nanometer w, float a) : wavelength(w), amplitude(a) {}
    };
    bool operator== (SpectrumSample const &lhs, SpectrumSample const &rhs) {
        return lhs.wavelength == rhs.wavelength && lhs.amplitude == rhs.amplitude;
    }
    bool operator!= (SpectrumSample const &lhs, SpectrumSample const &rhs) {
        return !(lhs == rhs);
    }
    bool rel_equal(SpectrumSample const &lhs, SpectrumSample const &rhs,
                   float max_rel_diff=std::numeric_limits<float>::epsilon())
    {
        return rel_equal(lhs.amplitude, rhs.amplitude, max_rel_diff)
            && rel_equal(lhs.wavelength, rhs.wavelength, max_rel_diff);
    }


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



    inline
    std::ostream& operator<< (std::ostream &os, Nanometer const &nm) {
        return os << static_cast<float>(nm) << "nm";
    }

    inline
    std::ostream& operator<< (std::ostream &os, SpectrumSample const &ss) {
        return os << ss.wavelength << ":" << ss.amplitude;
    }

    inline
    std::ostream& operator<< (std::ostream &os, Spectrum const &spec) {
        os << "spectrum{" << spec.lambda_min() << ".." << spec.lambda_max() << ", [";
        if (!spec.empty())
            os << spec[0];
        for (size_t i=1; i!=spec.size(); ++i)
            os << ", " << spec[i];
        return os << "]}";
    }
}


#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

bool is_nan_or_infinity (float f) {
    return (f != f) || (f==1.0f/0.0f) || (f==-1.0f/0.0f);
}

TEST_CASE("/internal", "RGB to HSV conversion")
{
    using namespace gaudy;

    auto spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2}));

    REQUIRE(400_nm == spec.lambda_min());
    REQUIRE(800_nm == spec.lambda_max());

    REQUIRE_FALSE(spec.empty());
    REQUIRE(spec.size() == 2);

    REQUIRE_THROWS(spec.at(-1));
    REQUIRE_NOTHROW(spec.at(0));
    REQUIRE_NOTHROW(spec.at(1));
    REQUIRE_THROWS(spec.at(2));
    REQUIRE_THROWS(spec.at(3));

    REQUIRE_NOTHROW(spec(0));
    REQUIRE_NOTHROW(spec(1));
    REQUIRE_THROWS(spec(1.01));
    REQUIRE_THROWS(spec(-0.01));
    REQUIRE_THROWS(spec(1.01));

    REQUIRE_NOTHROW(spec(400_nm));
    REQUIRE_NOTHROW(spec(400.1_nm));
    REQUIRE_NOTHROW(spec(800_nm));
    REQUIRE_THROWS(spec(399.9_nm));
    REQUIRE_THROWS(spec(800.1_nm));
    REQUIRE_THROWS(spec(-1_nm));

    REQUIRE_NOTHROW(spec(Interval<float>(0,1)));
    REQUIRE_NOTHROW(spec(Interval<float>(0,0)));
    REQUIRE_NOTHROW(spec(Interval<float>(1,1)));
    REQUIRE_THROWS(spec(Interval<float>(-0.001,1)));
    REQUIRE_THROWS(spec(Interval<float>(-2,-1)));
    REQUIRE_THROWS(spec(Interval<float>(1,2)));

    REQUIRE(spec[0] == SpectrumSample(400_nm, 1.0f));
    REQUIRE(spec[1] == SpectrumSample(800_nm, 2.0f));

    REQUIRE(spec(0)     == SpectrumSample(400_nm,   1.0f));
    REQUIRE(spec(0.25)  == SpectrumSample(500_nm,   1.25f));
    REQUIRE(spec(0.5)   == SpectrumSample(600_nm,   1.5f));
    REQUIRE(spec(0.75)  == SpectrumSample(700_nm,   1.75f));
    REQUIRE(rel_equal (spec(0.999), SpectrumSample(799.6_nm, 1.999f)));
    REQUIRE(spec(1)     == SpectrumSample(800_nm,   2.0f));

    REQUIRE(spec(400_nm)   == SpectrumSample(400_nm,   1.0f));
    REQUIRE(spec(500_nm)   == SpectrumSample(500_nm,   1.25f));
    REQUIRE(spec(600_nm)   == SpectrumSample(600_nm,   1.5f));
    REQUIRE(spec(700_nm)   == SpectrumSample(700_nm,   1.75f));
    REQUIRE(spec(799.6_nm) == SpectrumSample(799.6_nm, 1.999f));
    REQUIRE(spec(800_nm)   == SpectrumSample(800_nm,   2.0f));

    REQUIRE(spec(Interval<float>(0,1)) == SpectrumSample(600_nm, 1.5f));
    REQUIRE(spec(Interval<float>(0.5,1)) == SpectrumSample(700_nm, 1.75f));
    REQUIRE(spec(Interval<float>(0.75,1)) == SpectrumSample(750_nm, 1.875f));


    spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2, 9}));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(0, 0.001)).amplitude));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(0, 0)).amplitude));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(0.2, 0.2)).amplitude));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(1, 1)).amplitude));

    REQUIRE(spec(0)    == SpectrumSample(400_nm, 1));
    REQUIRE(spec(0.25) == SpectrumSample(500_nm, 1.5));
    REQUIRE(spec(0.5)  == SpectrumSample(600_nm, 2));
    REQUIRE(spec(0.75) == SpectrumSample(700_nm, 5.5));
    REQUIRE(spec(1)    == SpectrumSample(800_nm, 9));

    REQUIRE(spec(400_nm) == SpectrumSample(400_nm, 1));
    REQUIRE(spec(600_nm) == SpectrumSample(600_nm, 2));
    REQUIRE(spec(800_nm) == SpectrumSample(800_nm, 9));

    REQUIRE(spec(Interval<float>(0   , 0   )) == SpectrumSample(400_nm, 1  ));
    REQUIRE(spec(Interval<float>(0   , 0.5 )) == SpectrumSample(500_nm, 1.5));
    REQUIRE(rel_equal(spec(Interval<float>(0   , 1  )), SpectrumSample(600_nm, 3.5)));
    REQUIRE(spec(Interval<float>(0.5 , 1   )) == SpectrumSample(700_nm, 5.5));
    REQUIRE(spec(Interval<float>(0.75, 1   )) == SpectrumSample(750_nm, 7.25));
    REQUIRE(spec(Interval<float>(1   , 1   )) == SpectrumSample(800_nm, 9  ));
    REQUIRE(spec(Interval<float>(0   , 0.25)) == SpectrumSample(450_nm, 1.25));
    REQUIRE(spec(Interval<float>(0.25, 1   )) == SpectrumSample(650_nm, 4.25));

    spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2, 9, 3, 7}));
    REQUIRE(spec(0)     == SpectrumSample(400_nm, 1));
    REQUIRE(spec(0.125) == SpectrumSample(450_nm, 1.5));
    REQUIRE(spec(0.25)  == SpectrumSample(500_nm, 2));
    REQUIRE(spec(0.5)   == SpectrumSample(600_nm, 9));
    REQUIRE(spec(0.75)  == SpectrumSample(700_nm, 3));
    REQUIRE(spec(0.875) == SpectrumSample(750_nm, 5));
    REQUIRE(spec(1)     == SpectrumSample(800_nm, 7));

    REQUIRE(spec(400_nm) == SpectrumSample(400_nm, 1));
    REQUIRE(spec(600_nm) == SpectrumSample(600_nm, 9));
    REQUIRE(spec(800_nm) == SpectrumSample(800_nm, 7));

    REQUIRE(spec(Interval<float>(0    , 0  )) == SpectrumSample(400_nm, 1  ));
    REQUIRE(spec(Interval<float>(0    , 0.5)) == SpectrumSample(500_nm, 3.5));
    REQUIRE(spec(Interval<float>(0    , 1  )) == SpectrumSample(600_nm, 4.5));
    REQUIRE(rel_equal(spec(Interval<float>(0.5, 1  )), SpectrumSample(700_nm, 5.5)));
    REQUIRE(spec(Interval<float>(1    , 1  )) == SpectrumSample(800_nm, 7  ));
    REQUIRE(rel_equal(spec(Interval<float>(0.125, 1  )), SpectrumSample(625_nm, 4.964285714)));
}



int main(int argc, char *argv[]) {
    // see also https://github.com/philsquared/Catch/blob/master/docs/own-main.md
    return Catch::Session().run(argc, argv);
}
