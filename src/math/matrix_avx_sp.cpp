#pragma once

#ifdef __AVX512__

#include <immintrin.h>
#include <smmintrin.h>
#include "math/Matrix.h"

template<>
void Matrix<float>::add(Matrix<float> &result, const Matrix<float> &B) const {
    for(int i = 0; i < this->size; i += 16) {
        __m512 a = _mm512_loadu_ps(&this->data[i]);
        __m512 b = _mm512_loadu_ps(&B.data[i]);
        __m512 avx_result = _mm512_add_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }
}

template<>
void Matrix<float>::sub(Matrix<float> &result, const Matrix<float> &B) const {
    for(int i = 0; i < this->size; i += 16) {
        __m512 a = _mm512_loadu_ps(&this->data[i]);
        __m512 b = _mm512_loadu_ps(&B.data[i]);
        __m512 avx_result = _mm512_sub_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }
}

template<>
void Matrix<float>::mul(Matrix<float> &result, const Matrix<float> &B) const {
    for(int i = 0; i < this->height; i++) {
        float *aRowStart = &this->data[i * this->width];

        for(int j = 0; j < B.width; j++) {
            __m256 cell = _mm256_setzero_ps();

            int k = 0;
            for (; k < this->width; k += 8) {
                __m256 row = _mm256_load_ps(&this->data[j + k * this->width]);
                __m256 col = _mm256_load_ps(&B.data[k + i * B.height]);
                cell += _mm256_dp_ps(row, col, 1);
    
            }

            for (k -= 8; k < this->width; k += 8) {
                // TODO
            }

            result[i + result.width * j] = _mm_cvtss_f32(_mm256_castps256_ps128(cell));
        }
    }
}

#endif
