
#include <immintrin.h>
#include <smmintrin.h>
#include "math/Matrix.h"
#include <cstdint>

#ifdef __AVX2__

template <>
void Matrix<float>::add(Matrix<float> &result, const Matrix<float> &other) const {
    uint32_t i = 8;

    for (; i < this->size; i += 8) {
        __m256 a = _mm256_load_ps(&this->data[i]);
        __m256 b = _mm256_load_ps(&other.data[i]);
        __m256 avx_result = _mm256_add_ps(a, b);
        _mm256_store_ps(&result[i], avx_result);
    }

    for (i -= 8; i < this->size; i++) {
        result[i] = this->data[i] + other.data[i];
    }
}

template <>
void Matrix<float>::sub(Matrix<float>& result, const Matrix<float>& B) const {
    uint32_t i = 0;
    
    if (this->width >= 8) {
        uint32_t n = this->size - 8;
        
        for (; i < n; i += 8) {
            __m256 a = _mm256_loadu_ps(&this->data[i]);
            __m256 b = _mm256_loadu_ps(&B.data[i]);
            __m256 avx_result = _mm256_sub_ps(a, b);
            _mm256_storeu_ps(&result[i], avx_result);
        }
    }

    for (; i < this->size; i++) {
        result[i] = this->data[i] - B.data[i];
    }
}

template <>
void Matrix<float>::mul(Matrix<float>& result, const Matrix<float>& other) const {
    uint32_t n = this->width - 8;

    for (uint32_t j = 0; j < this->height; j++) {
        for (uint32_t i = 0; i < other.width; i++) {
            __m256 cell = _mm256_setzero_ps();

            uint32_t k = 0;

            if (this->width >= 8) {
                for (; k < n; k += 8) {
                    __m256 row = _mm256_load_ps(&this->data[k + j * this->width]);
                    __m256 col = _mm256_load_ps(&other.data[i + k * other.width]);
                    cell += _mm256_dp_ps(row, col, 1);
                }
            }

            for (; k < this->width; k++) {
                cell += this->data[k + j * this->width] * other[i + k * other.width];
            }

            result[i + result.width * j] = _mm_cvtss_f32(_mm256_castps256_ps128(cell));
        }
    }
}

#endif
