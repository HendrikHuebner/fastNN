//
// Created by hhuebner on 3/3/24.
//

#include "math/Dense32.h"

#define USE_AVX

#ifdef USE_AVX

#else


Dense32 Dense32::sub(const Dense32 &o) const {
    return Dense32(0, 0);
}

Dense32 Dense32::add(const Dense32 &o) const {
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

#endif