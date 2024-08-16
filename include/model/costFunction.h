//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_COSTFUNCTION_H
#define FASTNN_COSTFUNCTION_H

#include "math/Vector.h"

enum CostFunction {
    QUADRATIC,
    CROSS_ENTROPY,
    KULLBACK_LEIBLER
};

float applyCostFunction(CostFunction costFunction, const Vector<float>& output, const Vector<float>& expected);

Vector<float> applyCostDerivative(CostFunction costFunction, const Vector<float>& output, const Vector<float>& expected);

#endif //FASTNN_COSTFUNCTION_H
