#pragma once

#include "math/Matrix.h"
#include <iostream>
#include <iomanip>

/**
 *  Pretty print Matrix
 */
template <typename T>
void pMat(const Matrix<T>& m) {
    const int columnWidth = 7;

    std::cout << "+";

    for (int i = 0; i < m.getWidth() * (columnWidth + 1) + 1; i++) {
        std::cout << "-";
    }

    std::cout << "+" << std::endl;

    for (int i = 0; i < m.getHeight(); i++) {
        std::cout << "| ";

        for (int j = 0; j < m.getWidth(); j++) {
            std::cout << std::fixed << std::setprecision(3) << std::setw(columnWidth)
                      << m[i * m.getWidth() + j] << " ";
        }

        std::cout << "|" << std::endl;
    }

    std::cout << "+";

    for (int i = 0; i < m.getWidth() * (columnWidth + 1) + 1; i++) {
        std::cout << "-";
    }

    std::cout << "+" << std::endl;
}

template <typename T>
void pVec(const Vector<T>& v) {
    const int columnWidth = 7;

    std::cout << "Vector(" << v.getSize() <<  "):  {";
    for (int i = 0; i < v.getSize(); i++) {
        if (i > 0) 
            std::cout << ", ";

        std::cout << std::fixed << std::setprecision(3) << std::setw(columnWidth) << v[i];
    }

    std::cout << " }" << std::endl;
}
