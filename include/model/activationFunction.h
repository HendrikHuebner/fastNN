#pragma once

#include "math/Vector.h"

enum ActivationFunction { RELU, SIGMOID, SOFTMAX };

Vector<float> apply(Vector<float>& vector, ActivationFunction f);

Vector<float> applyDerivative(Vector<float>& vector, ActivationFunction f);
