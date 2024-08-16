#pragma once

#include <stdexcept>
#include <vector>
#include <cstdint>
#include "Vector.h"
#include "util/helpers.h"

/**
 * Generic Matrix class with trivial implementation of different operations.
 */
template<typename T, typename = enable_if_float<T>>
class Matrix {

private:
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

    T& operator[](const size_t index) {
        return data[index];
    }

    T operator[](const size_t index) const {
        return data[index];
    }

    void set(const int x, const int y, T f) {
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

    void add(Matrix<T>& result, const Matrix<T>& other) const  {

        if (this->width != other.width || this->height != other.height) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                result[i * this->width + j] += other[i * this->width + j];
            }
        }
    }

    void sub(Matrix<T>& result, const Matrix<T> &other) const {

        if (this->width != other.width || this->height != other.height) {
            throw std::invalid_argument("Matrix dimensions do not match");

        } else if (this->width != result->width || this->height != result->height) {
            throw std::invalid_argument("Result matrix dimensions do not match");
        }
        
        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                result[i * this->width + j] -= other[i * this->width + j];
            }
        }
    }

    void mul(Matrix<T>& result, const Matrix<T>& other) const {
        
        if (this->width != other.height) {
            throw std::invalid_argument("Operand size mismatch, cannot multiply matrices.");
        
        } else if (result->width != other->width || result->height != this->height) {
            throw std::invalid_argument("Result matrix size does not match operands, cannot multiply matrices.");
        }

        for (int i = 0; i < other.width; i++) {
            for (int j = 0; j < other.height; j++) {
                float cell = 0;

                for (int k = 0; k < this->height; k++) {
                    cell += this->data[j + k * this->width] * other[k + other.width * i];
                }

                result[i + result.width*j] = cell;
            }
        }
    }

    void mul(Vector<T> &result, const Vector<T> &other) const {
        if (this->height != other.length()) {
            throw std::invalid_argument("Matrix height must equal vector size");
        }

        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->height; j++) {
                result[i] += this->data[j + i * this->width] * other[j];
            }
        }
    }

    void transpose(const Matrix<T>& result) const {
        if (this->width != result->width || this->height != result->height) {
            throw std::invalid_argument("Result matrix size mismatch, cannot transpose matrix.");
        }

        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                result[i * this->width + j] = this->data[j * this->width + i];
            }
        }
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        Matrix<T> result(this->width, this->height);
        this->add(result, other);
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        Matrix<T> result(this->width, this->height);
        this->sub(result, other);
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        Matrix<T> result(other->width, this->height);
        this->mul(result, other);
        return result;
    }

    Vector<T> operator*(const Vector<T>& other) const {
        Vector<T> result(this->height);
        this->mul(result, other);
        return result;
    }
};
