//
// Created by hhuebner on 12/19/23.
//

#ifndef FASTNN_MATRIX_H
#define FASTNN_MATRIX_H


#include <vector>
#include <cstdint>
#include "Vector.h"
#include "util/helpers.h"

template<typename T, typename = enable_if_float<T>>
class Matrix {

public:
    T *data;
    const uint64_t size;
    const uint32_t height;
    const uint32_t width;

public:
    Matrix(uint32_t width, uint32_t height) : width(width), height(height), size(width * height) {
        this->data = new T[this->size];
    }

    Matrix(const Matrix& copy) : width(copy.width), height(copy.height), size(copy.size), data(copy.data) {}

    ~Matrix() { delete[] data; }

    T& operator[](size_t index) {
        return data[index];
    }

    T operator[](size_t index) const {
        return data[index];
    }

    void set(int x, int y, T f) {
        this->data[x + y * this->width] = f;
    }

    uint32_t getWidth() const {
        return this->width;
    }

    uint32_t getHeight() const {
        return this->height;
    }

    uint64_t getSize() const {
        return this->size;
    }

    T* getData() {
        return data;
    }

    std::vector<T> toStdVector() {
        return std::vector(this->data, this->data + this->size);
    }

    virtual Matrix<T> add(const Matrix<T>& other) const;

    virtual Matrix<T> sub(const Matrix<T> &o) const;

    virtual Matrix<T> mul(const Matrix<T>& other) const;

    virtual Vector<T> mul(const Vector<T> &o) const;

    virtual Matrix<T> transpose() const;
};


#endif //FASTNN_MATRIX_H
