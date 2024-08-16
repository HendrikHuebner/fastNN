//
// Created by hhuebner on 12/20/23.
//

#ifndef FASTNN_VECTOR_H
#define FASTNN_VECTOR_H


#include <cstddef>
#include <vector>
#include <stdint.h>
#include "util/helpers.h"

template <typename T, typename = enable_if_float<T>>
class Vector {

private:
    float *data;
    size_t size;

public:

    Vector(size_t size, float init) : size(size) {
        this->data = new float[size];
        std::fill_n(this->data, size, init);
    }

    Vector(const Vector& copy) : data(copy.data), size(copy.size) {}
    
    ~Vector() { delete[] data; }

    size_t length() const {
        return this->size;
    }

    float& operator[](size_t index) {
        return data[index];
    }

    float operator[](size_t index) const {
        return data[index];
    }

    std::vector<float> toStdVector() {
        return std::vector(data, data + this->size);
    }

    /**
     * Element wise addition
     */
    Vector add(const Vector& other) const;

    Vector sub(const Vector& other) const;


    /**
     * Element wise multiplication
     */
    Vector mul(const Vector& other) const;

    Vector div(const Vector& other) const;


    /**
     * Scalar multiplication
     */
    Vector scale(float scalar) const;


    float max();


    Vector clamp(float min, float max) const;
};


#endif //FASTNN_VECTOR_H
