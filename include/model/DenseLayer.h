//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_DENSELAYER_H
#define FASTNN_DENSELAYER_H


#include "model/Layer.h"
#include "model/activationFunction.h"
#include "math/Matrix.h"
#include "weightInit.h"

class DenseLayer : Layer {
private:

    const ActivationFunction activationFunction;
    const WeightInit weightInit;
    const int inputSize;
    const int outputSize;
    const int parameterCount;

    Matrix weights;
    Vector biases;
    Vector zValues;
    Vector aValues;

public:
    DenseLayer(const ActivationFunction activationFunction, const WeightInit weightInit, const int inputSize, const int outputSize):
    activationFunction(activationFunction),
    weightInit(weightInit),
    inputSize(inputSize),
    outputSize(outputSize),
    parameterCount(outputSize + inputSize * outputSize),
    weights(inputSize, outputSize),
    biases(outputSize, 0.0f),
    zValues(outputSize, 0.0f),
    aValues(inputSize, 0.0f) {}

    void init(std::mt19937 &rand);

    virtual int getParameterCount() const {
        return this->parameterCount;
    }

    virtual std::vector<float> getParameters() const;

    virtual void setParameters(const std::vector<float>& floats);

    Vector processInput(Vector inputs);
};


#endif //FASTNN_DENSELAYER_H
