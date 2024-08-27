#pragma once

#include "math/Vector.h"

enum CostFunction { QUADRATIC, CROSS_ENTROPY, KULLBACK_LEIBLER };

float applyCostFunction(CostFunction costFunction, const Vector<float>& output,
                        const Vector<float>& expected);

Vector<float> applyCostDerivative(CostFunction costFunction, const Vector<float>& output,
                                  const Vector<float>& expected);
