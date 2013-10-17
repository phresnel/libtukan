Execute('./bootstrap')

env = Environment(CPPPATH = ['.', 'bootstrapped/Catch/include/', 'include'],
                  CXXFLAGS = "-std=c++0x -Wall -O3 -ffast-math -march=native -msse2 -fopenmp ",
                  CPPFLAGS=""
                  )

gaudy = env.Program(target='gaudy',
                    source=['main.cc',
                            'src/Nanometer.cc'],
                    LIBS=['gomp']
                    )

Default(gaudy)

def PhonyTarget(target, action):
    import os
    phony = Environment(ENV = os.environ,
                        BUILDERS = { 'phony' : Builder(action = action) })
    AlwaysBuild(phony.phony(target = target, source = 'SConstruct'))

PhonyTarget('test', './gaudy test')
Depends('test', gaudy)
