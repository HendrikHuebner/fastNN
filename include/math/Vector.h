#pragma once

#include <cstddef>
#include <vector>
#include <stdint.h>
#include "util/helpers.h"

template <typename T, typename = enable_if_float<T>>
class Vector {

private:
    T *data;
    size_t size;

public:

    Vector(size_t size, T init) : size(size) {
        this->data = new T[size];
        std::fill_n(this->data, size, init);
    }

    Vector(const Vector& copy) : data(copy.data), size(copy.size) {}
    
    ~Vector() { delete[] data; }

    size_t length() const {
        return this->size;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T operator[](size_t index) const {
        return data[index];
    }
 
    std::vector<T> toStdVector() const {
        return std::vector(data, data + this->size);
    }

    void add(Vector<T> &result, const Vector& other) const {
        for (int i = 0; i < this->length(); i++) {
            result.data[i] += this->data[i];
        }
    }

    void sub(Vector<T> &result, const Vector& other) const {
        for (int i = 0; i < this->length(); i++) {
            result.data[i] -= this->data[i];
        }
    }

    /**
     * Element wise multiplication
     */
    void mul(Vector<T> &result, const Vector& other) const {
        for (int i = 0; i < this->length(); i++) {
            result.data[i] *= this->data[i];
        }
    }

    void mul(Vector<T> &result, T scalar) const {
        for (int i = 0; i < this->length(); i++) {
            result.data[i] = this->data[i] * scalar;
        }
    }

    void div(Vector<T> &result, const Vector& other) const {
        for (int i = 0; i < this->length(); i++) {
            result.data[i] /= this->data[i];
        }
    }

    T dot(const Vector& other) const {
        T sum(0.0);
        for (int i = 0; i < this->length(); i++) {
            sum += this[i] * other[i];
        }

        return sum;
    }

    T max() const {
        T max(0.0);
        for (int i = 0; i < this->length(); i++) {
            max = (this[i] > max) ? this[i] : max;
        }

        return max;
    }

    static inline T clamp(T x, T min, T max) {
        if (x < min) 
            return min;
        
        if (x > max)
            return max;

        return x;
    }

    void clamp(Vector<T> &result, T min, T max) const {
        for (int i = 0; i < this->length(); i++) {
            this[i] = clamp(this[i], min, max);
        }
    }

    Vector<T> operator+(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->add( result, other);
        return result;
    }

    Vector<T> operator-(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->sub( result, other);
        return result;
    }

    Vector<T> operator*(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->mul( result, other);
        return result;
    }

    Vector<T> operator/(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->div( result, other);
        return result;
    }

    Vector<T> operator*(const T other) const {
        Vector<T> result(this->size);
        this->mul( result, other);
        return result;
    }

};
