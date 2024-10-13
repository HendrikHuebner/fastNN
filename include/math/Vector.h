#pragma once

#include <stdint.h>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include "util/helpers.h"
#include <cstring>

template <typename T, typename = enable_if_float<T>>
class Vector {

   private:
    T* data;
    size_t size;

   public:
    Vector(size_t size) : size(size) {
        size_t s = ((sizeof(T) * size + 31) / 32) * 32;
        this->data = static_cast<T*>(std::aligned_alloc(32, s));
    }

    Vector(size_t size, T init) : Vector(size) {
        std::fill_n(this->data, size, init);
    }

    Vector(std::initializer_list<T> list) : Vector(list.size()) {
        std::memcpy(this->data, list.begin(), this->size * sizeof(T));
    }

    Vector(const Vector& copy) : data(copy.data), size(copy.size) {}

    Vector& operator=(const Vector& other) = default;

    size_t length() const { return this->size; }
    
    size_t getSize() const { return this->size; }

    ~Vector() { delete[] data; }

    T& operator[](size_t index) { return data[index]; }

    T operator[](size_t index) const { return data[index]; }

    std::vector<T> toStdVector() const { return std::vector(data, data + this->size); }

    void add(Vector<T>& result, const Vector& other) const {
        for (uint32_t i = 0; i < this->length(); i++) {
            result.data[i] = this->data[i] + other.data[i];
        }
    }

    void sub(Vector<T>& result, const Vector& other) const {
        for (uint32_t i = 0; i < this->length(); i++) {
            result.data[i] = this->data[i] - other.data[i];
        }
    }

    /**
     * Element wise multiplication
     */
    void mul(Vector<T>& result, const Vector& other) const {
        for (uint32_t i = 0; i < this->length(); i++) {
            result.data[i] = this->data[i] * other.data[i];
        }
    }

    void mul(Vector<T>& result, T scalar) const {
        for (uint32_t i = 0; i < this->length(); i++) {
            result.data[i] = this->data[i] * scalar;
        }
    }

    void div(Vector<T>& result, const Vector& other) const {
        for (uint32_t i = 0; i < this->length(); i++) {
            result.data[i] = this->data[i] / other.data[i];
        }
    }

    T dot(const Vector& other) const {
        T sum(0.0);
        for (uint32_t i = 0; i < this->length(); i++) {
            sum += this->data[i] * other.data[i];
        }

        return sum;
    }

    T max() const {
        T max(0.0);
        for (uint32_t i = 0; i < this->length(); i++) {
            max = (this->data[i] > max) ? this->data[i] : max;
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

    void clamp(Vector<T>& result, T min, T max) const {
        for (uint32_t i = 0; i < this->length(); i++) {
            result[i] = clamp(this->data[i], min, max);
        }
    }

    bool operator==(const Vector<T>& other) const {
        if (this->size != other.getSize())
            return false;

        for (uint32_t i = 0; i < this->size; i++) {
            if (this->data[i] != other.data[i])
                return false;
        }
        
        return true;
    }

    Vector<T> operator+(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->add(result, other);
        return result;
    }

    Vector<T> operator-(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->sub(result, other);
        return result;
    }

    Vector<T> operator*(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->mul(result, other);
        return result;
    }

    Vector<T> operator/(const Vector<T>& other) const {
        Vector<T> result(this->size);
        this->div(result, other);
        return result;
    }

    Vector<T> operator*(const T other) const {
        Vector<T> result(this->size);
        this->mul(result, other);
        return result;
    }
};
