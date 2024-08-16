//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_DENSELAYER_H
#define FASTNN_DENSELAYER_H


#include "model/Layer.h"
#include "model/activationFunction.h"
#include "math/Matrix.h"
#include "weightInit.h"

class DenseLayer : protected Layer {

protected:
    const ActivationFunction activationFunction;
    const WeightInit weightInit;
    const int parameterCount;

    Matrix<float> weights;
    Vector<float> biases;
    Vector<float> zValues;

public:
    DenseLayer(const ActivationFunction activationFunction, const WeightInit weightInit, const int inputSize, const int outputSize):
    Layer(inputSize, outputSize),
    activationFunction(activationFunction),
    weightInit(weightInit),
    parameterCount(outputSize + inputSize * outputSize),
    weights(inputSize, outputSize),
    biases(outputSize, 0.0f),
    zValues(outputSize, 0.0f) {}

    void init(std::mt19937 &rand) override;

    virtual int getParameterCount() const override {
        return this->parameterCount;
    }

    Vector<float> calculateError(Layer* previous, const Vector<float> nableCost) override;

    Matrix<float>* getWeights() {
        return &this->weights;
    }

    Vector<float> getBiases() {
        return this->biases;
    }

    void processInput(const Vector<float>& inputs) override;
};


#endif //FASTNN_DENSELAYER_H
