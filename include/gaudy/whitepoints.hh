// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef WHITEPOINTS_HH_INCLUDED_20131213
#define WHITEPOINTS_HH_INCLUDED_20131213

namespace gaudy { namespace whitepoint {
    // TODO: with C++14, the whitepoints should be variable templates.
    // Whitepoints from: http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html
    static constexpr XYZ<double> A   {1.09850, 1.00000, 0.35585};
    static constexpr XYZ<double> B   {0.99072, 1.00000, 0.85223};
    static constexpr XYZ<double> C   {0.98074, 1.00000, 1.18232};
    static constexpr XYZ<double> D50 {0.96422, 1.00000, 0.82521};
    static constexpr XYZ<double> D55 {0.95682, 1.00000, 0.92149};
    static constexpr XYZ<double> D65 {0.95047, 1.00000, 1.08883};
    static constexpr XYZ<double> D75 {0.94972, 1.00000, 1.22638};
    static constexpr XYZ<double> E   {1.00000, 1.00000, 1.00000};
    static constexpr XYZ<double> F2  {0.99186, 1.00000, 0.67393};
    static constexpr XYZ<double> F7  {0.95041, 1.00000, 1.08747};
    static constexpr XYZ<double> F11 {1.00962, 1.00000, 0.64350};
} }

#endif // WHITEPOINTS_HH_INCLUDED_20131213
