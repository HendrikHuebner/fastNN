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

    Matrix weights;
    Vector biases;
    Vector zValues;

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

    Vector calculateError(Layer* previous, const Vector nableCost);

    //virtual std::vector<float> getParameters() const;

    //virtual void setParameters(const std::vector<float>& floats);

    void processInput(const Vector& inputs) override;
};


#endif //FASTNN_DENSELAYER_H
