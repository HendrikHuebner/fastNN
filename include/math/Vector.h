//
// Created by hhuebner on 12/20/23.
//

#ifndef FASTNN_VECTOR_H
#define FASTNN_VECTOR_H


#include <vector>

class Vector {

private:
    std::vector<float> data;

public:

    Vector() = default;

    Vector(size_t size, float init) {
        this->data = std::vector<float>(size, init);
    }

    Vector(const Vector& copy) : data(copy.data) {}

    [[nodiscard]] size_t size() const {
        return this->data.size();
    }

    float& operator[](size_t index) {
        return data[index];
    }

    float operator[](size_t index) const {
        return data[index];
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
