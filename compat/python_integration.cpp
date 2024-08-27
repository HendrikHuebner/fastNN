//
// Created by hhuebner on 3/1/24.
//

#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void test() {
    std::cout << "Hello World" << std::endl;
}

PYBIND11_MODULE(pyfastNN, m) {
    m.def("hello", &test, "A function that says hello");
}
