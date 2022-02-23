#!/usr/bin/env python
from skbuild import setup


setup(name='multineat',
      version='0.7',  # Update version in conda/meta.yaml as well
      packages=['multineat'],
      cmake_args=['-DGENERATE_PYTHON_BINDINGS:BOOL=ON', '-DCMAKE_BUILD_TYPE=Release'],
      install_requires=['numpy'],
      )
