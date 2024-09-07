#pragma once

#include "DenseLayer.h"
#include "activationFunction.h"
#include "math/Vector.h"

class OutputLayer : protected DenseLayer {

    Vector<float> calculateError(Layer* layer, const Vector<float> nableCost) override {
        return nableCost * applyDerivative(this->zValues, this->activationFunction);
    }
};
