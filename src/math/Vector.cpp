//
// Created by hhuebner on 12/20/23.
//

#include <limits>
#include "math/Vector.h"

template<>
Vector<float> Vector<float>::add(const Vector<float> &other) const {

    Vector result(other);

    for (int i = 0; i < this->length(); i++) {
        result.data[i] += this->data[i];
    }

    return result;
}

template<>
Vector<float> Vector<float>::sub(const Vector<float> &other) const {

    Vector<float> result(other);

    for (int i = 0; i < this->length(); i++) {
        result.data[i] -= this->data[i];
    }

    return result;
}

template<>
Vector<float> Vector<float>::mul(const Vector<float> &other) const {
    Vector<float> result(other);

    for (int i = 0; i < this->length(); i++) {
        result.data[i] *= this->data[i];
    }

    return result;
}

template<>
Vector<float> Vector<float>::div(const Vector<float> &other) const {
    Vector<float> result(other);

    for (int i = 0; i < this->length(); i++) {
        result.data[i] /= this->data[i];
    }

    return result;
}

template<>
Vector<float> Vector<float>::scale(float scalar) const {
    Vector<float> result(*this);

    for (int i = 0; i < this->length(); i++) {
        result.data[i] *= scalar;
    }

    return result;
}

template<>
float Vector<float>::max() {
    float max = -std::numeric_limits<float>::infinity();

    for (int i = 0; i < this->length(); i++) {
        if (this->data[i] > max) {
            max = this->data[i];
        }
    }

    return max;
}

template<>
Vector<float> Vector<float>::clamp(float min, float max) const {
    Vector<float> result(*this);

    for (int i = 0; i < this->length(); i++) {
        if(result[i] > max) {
            result[i] = max;
        } else if(result[i] < min) {
            result[i] = min;
        }
    }

    return result;
}
