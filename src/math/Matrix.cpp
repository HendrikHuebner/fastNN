//
// Created by hhuebner on 12/19/23.
//

#include <stdexcept>
#include "math/Matrix.h"
#include "math/Vector.h"


Matrix Matrix::add(const Matrix& o) const {

    if (this->width != o.width || this->height != o.height) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }

    Matrix result(*this);

    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            result.data[i * this->width + j] += o.data[i * this->width + j];
        }
    }

    return result;
}

Matrix Matrix::sub(const Matrix& o) const {

    if (this->width != o.width || this->height != o.height) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }

    Matrix result(*this);

    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            result.data[i * this->width + j] -= o.data[i * this->width + j];
        }
    }

    return result;
}

Matrix Matrix::mul(const Matrix& o) const {
    Matrix result(this->height, o.width);

    for (int i = 0; i < o.width; i++) {
        for (int j = 0; j < o.height; j++) {
            float cell = 0;

            for (int k = 0; k < this->height; k++) {
                cell += this->data[j + k * this->width] * o.data[k + o.width * i];
            }

            result.data[i + result.width*j] = cell;
        }
    }

    return result;
}

Vector Matrix::mul(const Vector& o) const {

    if (this->height != o.size()) {
        throw std::invalid_argument("Matrix height must equal vector size");
    }

    Vector result(o.size(), 0.0f);

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            result.data[i] += this->data[j + i * this->width] * o.data[j];
        }
    }

    return result;
}

Matrix Matrix::transpose() {
    Matrix result(this->width, this->height);

    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            result.data[i * this->width + j] = this->data[j * this->width + i];
        }
    }

    return result;
}

