//
// Created by hhuebner on 12/19/23.
//

#ifndef FASTNN_MATRIX_H
#define FASTNN_MATRIX_H


#include <vector>
#include "Vector.h"

class Matrix {
public:
    Matrix(int width, int height) {
        this->width = width;
        this->height = height;

        this->data = std::vector<float>(width * height);
    }

    Matrix(const Matrix& copy) {
        this->width = copy.width;
        this->height = copy.height;
        this->data = copy.data;
    }

    float& operator[](size_t index) {
        return data[index];
    }

    float operator[](size_t index) const {
        return data[index];
    }

    Matrix add(const Matrix& other) const;

    Matrix sub(const Matrix &o) const;

    Matrix mul(const Matrix& other) const;

    Vector mul(const Vector &o) const;

    Matrix transpose() const;


private:
    int width;
    int height;
    std::vector<float> data;
};


#endif //FASTNN_MATRIX_H
