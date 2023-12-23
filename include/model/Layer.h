//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_LAYER_H
#define FASTNN_LAYER_H


#include <random>
#include <memory>
#include "math/Vector.h"

class Layer {

protected:
    const int inputSize;
    const int outputSize;
    Vector activationVec;

public:
    Layer(int inputSize, int outputSize) :
    inputSize(inputSize), outputSize(outputSize), activationVec(outputSize, 0.0f) {}

    virtual int getOutputSize() {
        return this->outputSize;
    }

    /**
     * Processes input from previous layer and updates activationVec
     * @param inputs
     */
    virtual void processInput(const Vector& inputs) = 0;

    /**
     * Initializes layer
     * @param rand
     */
    virtual void init(std::mt19937& rand) = 0;

    Vector getActivationVec() {
        return this->activationVec;
    }

    virtual int getParameterCount() const {
        return 0;
    }

    virtual Vector calculateError(Layer* previous, const Vector prevError) = 0;

    //virtual std::vector<float> getParameters() const;

    //virtual void setParameters(const std::vector<float>& floats);

    virtual ~Layer() = default;
};


#endif //FASTNN_LAYER_H
