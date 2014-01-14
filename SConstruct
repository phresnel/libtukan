Execute('./bootstrap')

env = Environment(CPPPATH = ['.', 'bootstrapped/Catch/include/', 'include'],
                  CXXFLAGS = "-std=c++11 -Wall -Wextra -fopenmp ",
                  CPPFLAGS=""
                  )

gaudy = env.Program(target='unit_tests',
                    source=['tests/main.cc',
                            'tests/Nanometer.cc',
                            'tests/Interval.cc',
                            'tests/LinearRGB.cc',
                            'tests/RGBSpace.cc',
                            'tests/RGB.cc',
                            'tests/XYZ.cc',
                            'tests/algorithm.cc',
                            'tests/algorithm/lerp.cc',
                            'tests/Matrix33.cc',
                            'tests/future/Spectrum.cc',
                            'tests/gammas.cc',
                           ],
                    LIBS=['gomp']
                    )

Default(gaudy)

def PhonyTarget(target, action):
    import os
    phony = Environment(ENV = os.environ,
                        BUILDERS = { 'phony' : Builder(action = action) })
    AlwaysBuild(phony.phony(target = target, source = 'SConstruct'))

PhonyTarget('test', './unit_tests')
Depends('test', gaudy)
