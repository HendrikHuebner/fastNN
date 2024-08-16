//
// Created by hhuebner on 3/5/24.
//

#ifndef FASTNN_MATRIX_OPS_H
#define FASTNN_MATRIX_OPS_H

#ifdef __AVX__

#include <immintrin.h>
#include <smmintrin.h>
#include "math/Dense32.h"

void add32(const Dense32 &A, const Dense32 &B, Dense32 &result) {
    for(int i = 0; i < A.size; i += 16) {
        __m512 a = _mm512_loadu_ps(&A.data[i]);
        __m512 b = _mm512_loadu_ps(&B.data[i]);
        __m512 avx_result = _mm512_add_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }
}

void sub32(const Dense32 &A, const Dense32 &B, Dense32 &result) {
    for(int i = 0; i < A.size; i += 16) {
        __m512 a = _mm512_loadu_ps(&A.data[i]);
        __m512 b = _mm512_loadu_ps(&B.data[i]);
        __m512 avx_result = _mm512_sub_ps(a, b);
        _mm512_storeu_ps(&result[i], avx_result);
    }
}

void mul32(const Dense32 &A, const Dense32 &B, Dense32 &result) {
    for(int i = 0; i < A.height; i++) {
        float *aRowStart = &A.data[i * A.width];

        for(int j = 0; j < B.width; j++) {
            __m256 cell = _mm256_setzero_ps();

            int k = 0;
            for (; k < A.width; k += 8) {
                __m256 row = _mm256_load_ps(&A.data[j + k * A.width]);
                __m256 col = _mm256_load_ps(&B.data[k + i * B.height]);
                cell += _mm256_dp_ps(row, col, 1);
    
            }

            for (k -= 8; k < A.width; k += 8) {
                // TODO
            }

            result[i + result.width * j] = _mm_cvtss_f32(_mm256_castps256_ps128(cell));
        }
    }
}

#endif

#endif //FASTNN_MATRIX_OPS_H
