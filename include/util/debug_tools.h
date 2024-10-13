#pragma once

#include "math/Matrix.h"
#include <cstdint>
#include <iostream>
#include <iomanip>

/**
 *  Pretty print Matrix
 */
template <typename T>
void printMatrix(const Matrix<T>& m) {
    const uint32_t columnWidth = 7;

    std::cout << "+";

    for (uint32_t i = 0; i < m.getWidth() * (columnWidth + 1) + 1; i++) {
        std::cout << "-";
    }

    std::cout << "+" << std::endl;

    for (uint32_t i = 0; i < m.getHeight(); i++) {
        std::cout << "| ";

        for (uint32_t j = 0; j < m.getWidth(); j++) {
            std::cout << std::fixed << std::setprecision(3) << std::setw(columnWidth)
                      << m[i * m.getWidth() + j] << " ";
        }

        std::cout << "|" << std::endl;
    }

    std::cout << "+";

    for (uint32_t i = 0; i < m.getWidth() * (columnWidth + 1) + 1; i++) {
        std::cout << "-";
    }

    std::cout << "+" << std::endl;
}

template <typename T>
void printVector(const Vector<T>& v) {
    const uint32_t columnWidth = 7;

    std::cout << "Vector(" << v.getSize() <<  "):  {";
    for (uint32_t i = 0; i < v.getSize(); i++) {
        if (i > 0) 
            std::cout << ", ";

        std::cout << std::fixed << std::setprecision(3) << std::setw(columnWidth) << v[i];
    }

    std::cout << " }" << std::endl;
}
