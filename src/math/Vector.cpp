//
// Created by hhuebner on 12/20/23.
//

#include <limits>
#include "math/Vector.h"

Vector Vector::add(Vector &other) {

    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] += this->data[i];
    }

    return result;
}

Vector Vector::sub(Vector &other) {

    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] -= this->data[i];
    }

    return result;
}


Vector Vector::mul(Vector &other) {
    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] += this->data[i];
    }

    return result;
}


Vector Vector::scale(float scalar) {
    Vector result(*this);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] *= scalar;
    }

    return result;
}

float Vector::max() {
    float max = -std::numeric_limits<float>::infinity();

    for (float f : this->data) {
        if (f > max) {
            max = f;
        }
    }

    return max;
}
