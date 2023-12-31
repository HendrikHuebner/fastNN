//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_OUTPUTLAYER_H
#define FASTNN_OUTPUTLAYER_H


#include "math/Vector.h"
#include "activationFunction.h"
#include "DenseLayer.h"

class OutputLayer : DenseLayer {

    Vector calculateError(Layer* _, const Vector nableCost) override {
        return nableCost.mul(applyDerivative(this->zValues, this->activationFunction));
    }

};


#endif //FASTNN_OUTPUTLAYER_H
