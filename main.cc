// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include <vector>
#include <valarray>
#include <iostream>
#include <stdexcept>

namespace gaudy {

    bool rel_equal (float lhs, float rhs, float max_rel_diff=std::numeric_limits<float>::epsilon())
    {
        // http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm

        // Calculate the difference.
        float diff = fabs(lhs - rhs);
        lhs = fabs(lhs);
        rhs = fabs(rhs);
        // Find the largest
        float largest = (rhs > lhs) ? rhs : lhs;

        return diff <= largest * max_rel_diff;
    }



    //----------------------------------------------------------------------------------------------
    // Nanometer
    //----------------------------------------------------------------------------------------------
    struct Nanometer {
        constexpr explicit Nanometer (float nm=0) noexcept : nm_(nm) {}
        constexpr explicit operator float() noexcept { return nm_; }
    private:
        float nm_;
    };

    // relation
    constexpr bool operator== (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) == static_cast<float>(rhs);
    }
    constexpr bool operator!= (Nanometer lhs, Nanometer rhs) noexcept {
        return !(lhs == rhs);
    }
    bool rel_equal (Nanometer lhs, Nanometer rhs,
                    float max_rel_diff=std::numeric_limits<float>::epsilon())
    {
        return rel_equal (static_cast<float>(lhs), static_cast<float>(rhs), max_rel_diff);
    }

    constexpr bool operator> (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) > static_cast<float>(rhs);
    }
    constexpr bool operator< (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) < static_cast<float>(rhs);
    }
    constexpr bool operator>= (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) >= static_cast<float>(rhs);
    }
    constexpr bool operator<= (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) <= static_cast<float>(rhs);
    }

    // arithmetic
    constexpr Nanometer operator+ (Nanometer rhs) noexcept {
        return rhs;
    }
    constexpr Nanometer operator- (Nanometer rhs) noexcept {
        return Nanometer(-static_cast<float>(rhs));
    }
    constexpr Nanometer operator+ (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) + static_cast<float>(rhs));
    }
    constexpr Nanometer operator- (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) - static_cast<float>(rhs));
    }
    constexpr Nanometer operator* (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) * static_cast<float>(rhs));
    }
    constexpr Nanometer operator/ (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) / static_cast<float>(rhs));
    }

    // literals ------------------------------------------------------------------------------------
    inline constexpr Nanometer operator"" _nm (long double nm) noexcept {
        return Nanometer(nm);
    }
    inline constexpr Nanometer operator"" _nm (unsigned long long nm) noexcept {
        return Nanometer(nm);
    }



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

            float frac = f - static_cast<int>(f);
            return SpectrumSample(g, bins_[i]*(1-frac) + bins_[i+1]*frac);
        }

        SpectrumSample operator() (Nanometer g) const {
            if (g<lambda_min_) throw std::logic_error("passed value < lambda_min to "
                                                      "Spectrum::operator()(Nanometer)");
            if (g>lambda_max_) throw std::logic_error("passed value > lambda_max to "
                                                      "Spectrum::operator()(Nanometer)");
            if (g == lambda_min_) return SpectrumSample(lambda_min(), bins_[0]);
            if (g == lambda_max_) return SpectrumSample(lambda_max(), bins_[size()-1]);

            float f = static_cast<float>((g - lambda_min_) / (lambda_max_-lambda_min_));
            int i = f*static_cast<float>(size()-1);

            float frac = f - static_cast<int>(f);
            return SpectrumSample(g, bins_[i]*(1-frac) + bins_[i+1]*frac);
        }

    private:
        Nanometer lambda_min_, lambda_max_;
        std::valarray<float> bins_;
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

namespace gaudy { namespace detail {

} }


#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
TEST_CASE("/internal", "RGB to HSV conversion")
{
    using namespace gaudy;

    REQUIRE(1_nm == 1_nm);
    REQUIRE(1_nm != 2_nm);
    REQUIRE(rel_equal(1_nm, 1_nm));
    REQUIRE((1_nm - 1_nm) == 0_nm);
    REQUIRE((1_nm + 1_nm) == 2_nm);
    REQUIRE((1_nm * 2_nm) == 2_nm);
    REQUIRE((1_nm / 2_nm) == 0.5_nm);
    REQUIRE(-(-1_nm) == 1_nm);
    REQUIRE(+1_nm == 1_nm);

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
}



int unit_tests(int argc, char *argv[]) {
    // see also https://github.com/philsquared/Catch/blob/master/docs/own-main.md
    return Catch::Session().run(argc, argv);
}

int main(int argc, char *argv[]) {

    if (argc >= 2 && argv[1]==std::string("test")) {
        // Short circuit the CLI arguments.
        argc -= 2;
        argv += 2;
        std::vector<std::string> args;
        args.push_back("gaudy test");
        while (*argv != 0) {
            args.push_back(*argv);
            ++argv;
        }
        std::vector<char*> args_c_str;
        for (auto &s : args)
            args_c_str.emplace_back(const_cast<char*>(s.c_str()));
        return unit_tests(args_c_str.size(), &args_c_str[0]);
    }
}
