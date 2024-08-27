#pragma once

#include "DenseLayer.h"
#include "activationFunction.h"
#include "math/Vector.h"

class OutputLayer : DenseLayer {

    Vector<float> calculateError(Layer* _, const Vector<float> nableCost) override {
        return nableCost * applyDerivative(this->zValues, this->activationFunction);
    }
};
