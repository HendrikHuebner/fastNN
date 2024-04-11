//
// Created by hhuebner on 12/20/23.
//

#ifndef FASTNN_VECTOR_H
#define FASTNN_VECTOR_H


#include <vector>
#include <cstdlib>

class Vector {

protected:
    float *data;
    const u_int32_t size;

public:

    Vector(size_t size, float init) : size(size) {
        this->data = new float[size];
        std::fill_n(this->data, size, init);
    }

    Vector(const Vector& copy) : data(copy.data), size(copy.size) {}


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
