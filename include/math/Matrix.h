#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "Vector.h"

#include <iostream>

/**
 * Generic Matrix class with trivial implementation of different operations.
 */
template <typename T>
class Matrix {

   private:
    T* data;
    const uint32_t width;
    const uint32_t height;
    const uint64_t size;

   public:
    Matrix(uint32_t width, uint32_t height) : width(width), height(height), size(width * height) {
        size_t s = ((sizeof(T) * size + 31) / 32) * 32;
        this->data = static_cast<T*>(std::aligned_alloc(32, s));
    }

    Matrix(uint32_t width, uint32_t height, T init) : Matrix(width, height) {
        std::fill_n(this->data, size, init);
    }

    Matrix(uint32_t width, uint32_t height, T init[]) : Matrix(width, height) {
        std::memcpy(this->data, init, this->size * sizeof(T));
    }

    explicit Matrix(const Matrix& copy) : Matrix(copy.width, copy.height) {
        std::memcpy(copy.data, this->data, copy.size * sizeof(T));
    }

    Matrix<T>& operator=(Matrix<T>& copy) = delete;
    
    Matrix<T>(Matrix<T>&&) = default;

    Matrix<T>& operator=(Matrix<T>&&) = default;
    
    ~Matrix() {  delete[] data; }

    static Matrix<T> ident(uint32_t size) {
        Matrix<T> m(size, size, (T) 0.0);
        for (uint32_t i = 0; i < size; i++) {
            m.data[i * (1 + size)] = 1.0;
        }
        return m;
    }

    T& operator[](const size_t index) { return data[index]; }

    T operator[](const size_t index) const { return data[index]; }

    void set(const uint32_t x, const uint32_t y, T f) { this->data[x + y * this->width] = f; }

    uint32_t getWidth() const { return this->width; }

    uint32_t getHeight() const { return this->height; }

    uint64_t getSize() const { return this->size; }

    T* getData() { return data; }

    std::vector<T> toStdVector() { return std::vector(this->data, this->data + this->size); }

    void add(Matrix<T>& result, const Matrix<T>& other) const {
        if (this->width != other.width || this->height != other.height) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        for (uint32_t i = 0; i < this->size; i++) {
            result[i] = this->data[i] + other[i];
        }
    }

    void sub(Matrix<T>& result, const Matrix<T>& other) const {

        if (this->width != other.width || this->height != other.height) {
            throw std::invalid_argument("Matrix dimensions do not match");

        } else if (this->width != result.width || this->height != result.height) {
            throw std::invalid_argument("Result matrix dimensions do not match");
        }

        for (uint32_t i = 0; i < this->size; i++) {
            result[i] = this->data[i] - other[i];
        }
    }

    void mul(Matrix<T>& result, const Matrix<T>& other) const {

        if (this->width != other.height) {
            throw std::invalid_argument("Operand size mismatch, cannot multiply matrices.");

        } else if (result.width != other.width || result.height != this->height) {
            throw std::invalid_argument(
                "Result matrix size does not match operands, cannot multiply matrices.");
        }

        for (uint32_t j = 0; j < this->height; j++) {
            for (uint32_t i = 0; i < other.width; i++) {
                float cell = 0;

                for (uint32_t k = 0; k < this->width; k++) {
                    cell += this->data[k + j * this->width] * other[i + other.width * k];
                }
                result.data[i + result.width * j] = cell;
            }
        }
    }

    void mul(Vector<T>& result, const Vector<T>& other) const {
        if (this->height != other.length()) {
            throw std::invalid_argument("Matrix height must equal vector size");
        }

        for (uint32_t i = 0; i < this->width; i++) {
            for (uint32_t j = 0; j < this->height; j++) {
                result[i] += this->data[j + i * this->width] * other[j];
            }
        }
    }

    void transpose(const Matrix<T>& result) const {
        if (this->width != result.height || this->height != result.width) {
            throw std::invalid_argument("Result matrix size mismatch, cannot transpose matrix.");
        }

        for (uint32_t i = 0; i < this->height; i++) {
            for (uint32_t j = 0; j < this->width; j++) {
                result.data[j * this->height + i] = this->data[i * this->width + j];
            }
        }
    }

    bool operator==(const Matrix<T>& other) const {
        if (this->size != other.getSize())
            return false;

        for (uint32_t i = 0; i < this->size; i++) {
            if (this->data[i] != other.data[i])
                return false;
        }
        
        return true;
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
        Matrix<T> result(other.width, this->height);
        this->mul(result, other);
        return result;
    }

    Vector<T> operator*(const Vector<T>& other) const {
        Vector<T> result(this->height);
        this->mul(result, other);
        return result;
    }
};


template <>
void Matrix<float>::add(Matrix<float>& result, const Matrix<float>& B) const;

template <>
void Matrix<float>::mul(Matrix<float>& result, const Matrix<float>& other) const;  
