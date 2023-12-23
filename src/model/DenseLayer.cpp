//
// Created by hhuebner on 12/21/23.
//

#include <stdexcept>
#include "model/DenseLayer.h"


void DenseLayer::init(std::mt19937 &rand) {

    for (int i = 0; i < this->weights.getWidth(); i++) {
        for (int j = 0; j < this->weights.getHeight(); j++) {
            this->weights.set(i, j, initializeWeight(this->weightInit, rand, this->inputSize));
        }
    }

    for(int i = 0; i < this->biases.size(); i++) {
        this->biases[i] = initializeWeight(this->weightInit, rand, this->inputSize);
    }
}

Vector DenseLayer::calculateError(Layer *previous, const Vector nableCost) {
    return previous->getActivationVec().mul(nableCost.mul(applyDerivative(this->zValues, this->activationFunction)));
}

void DenseLayer::processInput(const Vector& inputs) {

    if (inputs.size() != this->inputSize)
        throw std::invalid_argument("DenseLayer received a greater amount of inputs than expected!");


    Vector activation = this->weights.mul(inputs).add(this->biases);

    this->zValues = activation;
    this->activationVec = apply(activation, this->activationFunction);
}

