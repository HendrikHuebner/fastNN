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

float applyCostFunction(CostFunction costFunction, const Vector& output, const Vector& expected);

Vector computeDerivative(CostFunction costFunction, const Vector& output, const Vector& expected);

#endif //FASTNN_COSTFUNCTION_H
