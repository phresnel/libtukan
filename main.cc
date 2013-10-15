// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include <vector>
#include <valarray>
#include <iostream>

namespace gaudy {



    //----------------------------------------------------------------------------------------------
    // Nanometer
    //----------------------------------------------------------------------------------------------
    struct Nanometer {
        constexpr explicit Nanometer (float nm=0) noexcept : nm_(nm) {}
        constexpr operator float() noexcept { return nm_; }
    private:
        float nm_;
    };

    inline constexpr Nanometer operator"" _nm (long double nm)        noexcept { return Nanometer(nm); }
    inline constexpr Nanometer operator"" _nm (unsigned long long nm) noexcept { return Nanometer(nm); }



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
        SpectrumSample  operator[] (size_t i) const {
            float f = (i / static_cast<float>(size()-1));
            f = lambda_min_ + f*(lambda_max_-lambda_min_);
            return SpectrumSample(Nanometer(f), bins_[i]);
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

    /*void interpolate (float lambda_min, float lambda_max, std::vector<float> source,
                      float target_lambda_min, float target_lambda_max, std::vector<float> &target)
    {
    }*/

} }


#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
TEST_CASE("/internal", "RGB to HSV conversion")
{
    using namespace gaudy;

    auto spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2}));

    REQUIRE(spec[0] == SpectrumSample(400_nm, 1.0f));
    REQUIRE(spec[1] == SpectrumSample(800_nm, 2.0f));

    std::cerr << spec << std::endl;
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
