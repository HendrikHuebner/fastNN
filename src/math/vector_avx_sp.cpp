#ifdef __AVX512__

#include <immintrin.h>
#include <smmintrin.h>
#include "math/Vector.h"
#include <cstdint>

template <>
void Vector<float>::add(Vector<float>& result, const Vector<float>& other) const {
    uint32_t i = 0;
    for (; i < this->size; i += 16) {
        __m512 a = _mm512_loadu_ps(&this->data[i]);
        __m512 b = _mm512_loadu_ps(&other.data[i]);
        __m512 avx_result = _mm512_add_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }

    for (i -= 16; i < this->size; i++) {
        result[i] = this->data[i] + other[i];
    }
}

template <>
void Vector<float>::sub(Vector<float>& result, const Vector<float>& other) const {
    uint32_t i = 0;
    for (; i < this->size; i += 16) {
        __m512 a = _mm512_loadu_ps(&this->data[i]);
        __m512 b = _mm512_loadu_ps(&other.data[i]);
        __m512 avx_result = _mm512_sub_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }

    for (i -= 16; i < this->size; i++) {
        result[i] = this->data[i] - other[i];
    }
}

template <>
void Vector<float>::mul(Vector<float>& result, const Vector<float>& other) const {
    uint32_t i = 0;
    for (; i < this->size; i += 16) {
        __m512 a = _mm512_loadu_ps(&this->data[i]);
        __m512 b = _mm512_loadu_ps(&other.data[i]);
        __m512 avx_result = _mm512_mul_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }

    for (i -= 16; i < this->size; i++) {
        result[i] = this->data[i] * other[i];
    }
}

#endif
