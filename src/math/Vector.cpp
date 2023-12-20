//
// Created by hhuebner on 12/20/23.
//

#include <limits>
#include "math/Vector.h"

Vector Vector::add(const Vector &other) const {

    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] += this->data[i];
    }

    return result;
}

Vector Vector::sub(const Vector &other) const {

    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] -= this->data[i];
    }

    return result;
}


Vector Vector::mul(const Vector &other) const {
    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] *= this->data[i];
    }

    return result;
}


Vector Vector::div(const Vector &other) const {
    Vector result(other);

    for (int i = 0; i < this->data.size(); i++) {
        result.data[i] /= this->data[i];
    }

    return result;
}

Vector Vector::scale(float scalar) const {
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

Vector Vector::clamp(float min, float max) const {
    Vector result(*this);

    for (int i = 0; i < this->data.size(); i++) {
        if(result[i] > max) {
            result[i] = max;
        } else if(result[i] < min) {
            result[i] = min;
        }
    }

    return result;
}
