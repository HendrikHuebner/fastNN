#pragma once

#ifdef __AVX512__

#include <immintrin.h>
#include <smmintrin.h>
#include "math/Vector.h"

template<>
void Vector<float>::add(Vector<float> &result, const Vector<float> &other) const {

}

template<>
void Vector<float>::sub(Vector<float> &result, const Vector<float> &other) const {

}

template<>
void Vector<float>::mul(Vector<float> &result, const Vector<float> &other) const {

}

#endif
