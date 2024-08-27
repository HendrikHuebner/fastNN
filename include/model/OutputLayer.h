//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_OUTPUTLAYER_H
#define FASTNN_OUTPUTLAYER_H

#include "DenseLayer.h"
#include "activationFunction.h"
#include "math/Vector.h"

class OutputLayer : DenseLayer {

    Vector<float> calculateError(Layer* _, const Vector<float> nableCost) override {
        return nableCost * applyDerivative(this->zValues, this->activationFunction);
    }
};

#endif  //FASTNN_OUTPUTLAYER_H
