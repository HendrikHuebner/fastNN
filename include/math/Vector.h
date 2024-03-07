//
// Created by hhuebner on 12/20/23.
//

#ifndef FASTNN_VECTOR_H
#define FASTNN_VECTOR_H


#include <vector>
#include <cstdlib>

template<class T>
class Vector {

protected:
    T *data;
     const u_int32_t size;

public:

    Vector() = default;

    Vector(size_t size, T init) : size(size) {
        this->data = new T[size];
        std::fill_n(this->data, size, init);
    }

    Vector(const Vector& copy) : data(copy.data) {}


    float& operator[](size_t index) {
        return data[index];
    }

    T operator[](size_t index) const {
        return data[index];
    }

    std::vector<T>& toStdVector() {
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


    T max();


    Vector clamp(float min, float max) const;
};


#endif //FASTNN_VECTOR_H
