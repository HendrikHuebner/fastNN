//
// Created by hhuebner on 12/20/23.
//

#ifndef FASTNN_VECTOR_H
#define FASTNN_VECTOR_H


#include <vector>

class Vector {
public:

    std::vector<float> data;

    Vector(int size, float init) {
        this->data = std::vector<float>(size, init);
    }

    Vector(Vector& copy) : data(copy.data) {}

    [[nodiscard]] unsigned long size() const {
        return this->data.size();
    }

    /**
     * Element wise addition
     */
    Vector add(Vector& other);

    Vector sub(Vector& other);


    /**
     * Element wise multiplication
     */
    Vector mul(Vector& other);


    /**
     * Scalar multiplication
     */
    Vector scale(float scalar);


    float max();
};


#endif //FASTNN_VECTOR_H
