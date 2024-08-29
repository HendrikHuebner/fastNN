# Neural Network library written in C++

Work in progress - this is not usable at the moment

A small neural network library written in C++

## TODOs
- [x] Basic non-parallel implementation on the CPU
- [ ] AVX512 accellerated linear algebra operations
- [ ] CUDA accellerated math and backpropagation
- [ ] half precision / bfloat support

- [x] Dense layers and backpropagation
- [ ] Convolutional layers
- [ ] Pooling layers

- [ ] python / numpy integration

## Build process and dependencies:

### dependencies
If Unit tests are built:
- GoogleTest, fetched automatically using cmake

If python language interface is built:
- pybind11, install with `apt install pybind11-dev` on Debian
- pybind11-stubgen, install with `pip3 install pybind11 pybind11-stubgen`

### Building and testing

Configure the project using cmake, e.g. by using one of the commands provided in the Justfile.

With the [just](https://github.com/casey/just) utility, you can simply configure the project and run the tests using
``just check-all``

Which simply runs the following commands:
```
    cmake -B ./build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DAVX_MODE=ON -DBUILD_TESTS=ON
    ninja -C ./build
    ctest --test-dir ./build --output-on-failure
```
Or run the commands one by one.
