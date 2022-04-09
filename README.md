# C++ processes executor from yaml config file 
_*technical task for basecamp students*_

## Build steps

1. [Clone](https://github.com/jbeder/yaml-cpp) `yaml-cpp` and build it following its build tutorial.

2. Build the program linking static library 
```
g++ -o result main.cpp process.cpp -lyaml-cpp -pthread -std=c++17
```
**Note:** specify `yaml-cpp` location for the linker in case the library is not located in your working directory
