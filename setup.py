from distutils.core import setup, Extension

module1 = Extension('gpio',
                    libraries = ['wiringPi'],
                    sources = ['gpiomodule.c'])

setup (name = 'GpioMethod',
       version = '1.0',
       description = 'WiringOP library Python wrapper',
       ext_modules = [module1])
