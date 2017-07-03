from distutils.core import setup, Extension
 
moduledemo = Extension('demo',
                    sources = ['demo.c'])
moduletest = Extension('testmodule',
                       sources = ['testmodule.c'])

setup (name = 'Demo hello',
       version = '1.0',
       description = 'This is a demo package by Sink',
       ext_modules = [moduledemo])

setup (name = 'Demo hello',
       version = '1.0',
       description = 'This is a with c function calls',
       ext_modules = [moduletest])