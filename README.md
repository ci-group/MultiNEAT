# About MultiNEAT

MultiNEAT is a portable software library for performing neuroevolution, a form of machine learning that
trains neural networks with a genetic algorithm. It is based on NEAT, an advanced method for evolving
neural networks through complexification. The neural networks in NEAT begin evolution with very simple
genomes which grow over successive generations. The individuals in the evolving population are grouped
by similarity into species, and each of them can compete only with the individuals in the same species.

The combined effect of speciation, starting from the simplest initial structure and the correct
matching of the genomes through marking genes with historical markings yields an algorithm which
is proven to be very effective in many domains and benchmarks against other methods.

NEAT was developed around 2002 by Kenneth Stanley in the University of Texas at Austin.

### License

GNU Lesser General Public License v3.0 

### Documentation
[http://multineat.com/docs.html](http://multineat.com/docs.html)

## Building and installation instructions

### Prerequisites

Install [Cereal](https://uscilab.github.io/cereal/)

For example on ubuntu:
```
sudo apt install libcereal-dev
```

If no package is available for your system, install from source.
The package is header only, so no building required.

### To install as a python library
  ```bash
  pip install .
  ```

### To install as a cpp library
  ```bash
  mkdir build && cd build
  cmake ..
  make -j4
  (sudo) make install
  ```
  
Installing options:
- if you want to install the release version without debugging symbols, add this option to the `cmake` command:
  ```
  cmake .. -DCMAKE_BUILD_TYPE=Release
  ```
  
- if you want to install the multineat in a different folder, add this option to the `cmake` command:
  ```
  cmake .. -CMAKE_INSTALL_PREFIX=/path/to/install/folder/
  ```
  
 These options may be combined togheter
