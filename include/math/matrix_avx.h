//
// Created by hhuebner on 3/5/24.
//

#ifndef FASTNN_MATRIX_OPS_H
#define FASTNN_MATRIX_OPS_H

#include <immintrin.h>
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
            float cell = 0;

            for (int k = 0; k < A.height; k += 16) {
                cell += A.data[j + k * A.width] * B.data[k + B.width * i];
            }

            result[i + result.width*j] = cell;
            __m512 b = _mm512_loadu_ps(&B.data[i]);
            __m512 avx_result = _mm512_add_ps(a, b);
            _mm512_storeu_ps(&result[i], avx_result);
        }
    }
}

#endif //FASTNN_MATRIX_OPS_H
