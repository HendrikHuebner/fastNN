# Neural Network library written in C++

Work in progress, hopefully there will be time to contiue this project during the winter break


## Build process and dependencies:

1. install the pybind11 library

    ``Debian: apt install pybind11-dev``


2. Install the pybind11 python module and stub-gen

    ``pip3 install pybind11 pybind11-stubgen``


3. Generate build files using cmake. e. g.:
    ``cmake -B ./build -G Ninja``


## math library

Relevant papers: 

- https://www.researchgate.net/publication/315365781_Strassen%27s_Algorithm_Reloaded

Intel intrinsics guide:

- https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html