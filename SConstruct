Execute('./bootstrap')

env = Environment(CPPPATH = ['.', 'bootstrapped/Catch/include/', 'include'],
                  CXXFLAGS = "-std=c++11 -Wall -Wextra -fopenmp ",
                  CPPFLAGS=""
                  )

gaudy = env.Program(target='unit_tests',
                    source=['main.cc',
                            'src/Nanometer.cc',
                            'src/Interval.cc',
                            'src/Spectrum.cc',
                            'src/LinearRGB.cc',
                            'src/RGBSpace.cc',
                            'src/XYZ.cc',
                            'src/algorithm.cc',
                            'src/algorithm/lerp.cc'
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
