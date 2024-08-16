//
// Created by hhuebner on 12/19/23.
//

#include <stdexcept>
#include "math/Matrix.h"
#include "math/Vector.h"


/**
 * Trivial implementation of a 32 bit float Matrix
 */
class Dense32 : public Matrix<float> {

public:
    Dense32(const uint32_t width, const uint32_t height) : Matrix<float>(width, height) {}

    Dense32 add(const Dense32& o) const {

        if (this->width != o.width || this->height != o.height) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        Dense32 result(*this);

        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                result[i * this->width + j] += o[i * this->width + j];
            }
        }

        return result;
    }

    Dense32 sub(const Dense32& o) const {

        if (this->width != o.width || this->height != o.height) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        Dense32 result(*this);

        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                result[i * this->width + j] -= o[i * this->width + j];
            }
        }

        return result;
    }

    Dense32 mul(const Dense32& o) const {
        Dense32 result(this->height, o.width);

        for (int i = 0; i < o.width; i++) {
            for (int j = 0; j < o.height; j++) {
                float cell = 0;

                for (int k = 0; k < this->height; k++) {
                    cell += this->data[j + k * this->width] * o[k + o.width * i];
                }

                result[i + result.width*j] = cell;
            }
        }

        return result;
    }

    Vector<float> mul(const Vector<float>& o) const {

        if (this->height != o.length()) {
            throw std::invalid_argument("Matrix height must equal vector size");
        }

        Vector<float> result(o.length(), 0.0f);

        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->height; j++) {
                result[i] += this->data[j + i * this->width] * o[j];
            }
        }

        return result;
    }

    Matrix<float> transpose() const {
        Dense32 result(this->width, this->height);

        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                result[i * this->width + j] = this->data[j * this->width + i];
            }
        }

        return result;
    }
};
