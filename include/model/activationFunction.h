//
// Created by hhuebner on 12/20/23.
//

#ifndef FASTNN_ACTIVATIONFUNCTION_H
#define FASTNN_ACTIVATIONFUNCTION_H


#include "math/Vector.h"

enum ActivationFunction {
    RELU,
    SIGMOID,
    SOFTMAX
};

Vector<float> apply(Vector<float>& vector, ActivationFunction f);

Vector<float> applyDerivative(Vector<float>& vector, ActivationFunction f);

#endif //FASTNN_ACTIVATIONFUNCTION_H
