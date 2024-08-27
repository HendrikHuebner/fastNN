#pragma once

#include <random>
#include "math/Vector.h"

class Layer {

   protected:
    const int inputSize;
    const int outputSize;
    Vector<float> activationVec;

   public:
    Layer(int inputSize, int outputSize)
        : inputSize(inputSize), outputSize(outputSize), activationVec(outputSize, 0.0f) {}

    virtual int getOutputSize() { return this->outputSize; }

    /**
     * Processes input from previous layer and updates activationVec
     * @param inputs
     */
    virtual void processInput(const Vector<float>& inputs) = 0;

    /**
     * Initializes layer
     * @param rand
     */
    virtual void init(std::mt19937& rand) = 0;

    Vector<float> getActivationVec() const { return this->activationVec; }

    virtual int getParameterCount() const { return 0; }

    virtual Vector<float> calculateError(Layer* previous, const Vector<float> prevError) = 0;

    virtual ~Layer() = default;
};

