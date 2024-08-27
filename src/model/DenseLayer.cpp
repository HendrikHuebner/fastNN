#include "model/DenseLayer.h"
#include <stdexcept>

void DenseLayer::init(std::mt19937& rand) {

    for (int i = 0; i < this->weights.getWidth(); i++) {
        for (int j = 0; j < this->weights.getHeight(); j++) {
            this->weights.set(i, j, initializeWeight(this->weightInit, rand, this->inputSize));
        }
    }

    for (int i = 0; i < this->biases.length(); i++) {
        this->biases[i] = initializeWeight(this->weightInit, rand, this->inputSize);
    }
}

Vector<float> DenseLayer::calculateError(Layer* previous, const Vector<float> nableCost) {
    return previous->getActivationVec() * nableCost *
           applyDerivative(this->zValues, this->activationFunction);
}

void DenseLayer::processInput(const Vector<float>& inputs) {

    if (inputs.length() != this->inputSize)
        throw std::invalid_argument(
            "DenseLayer received a greater amount of inputs than expected!");

    Vector activation = this->weights * inputs + this->biases;

    this->zValues = activation;
    this->activationVec = apply(activation, this->activationFunction);
}
