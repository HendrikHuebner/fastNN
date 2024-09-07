#pragma once

#include <random>
#include "math/Vector.h"

class Layer {

   protected:
    const uint32_t inputSize;
    const uint32_t outputSize;
    Vector<float> activationVec;

   public:
    Layer(uint32_t inputSize, uint32_t outputSize)
        : inputSize(inputSize), outputSize(outputSize), activationVec(outputSize, 0.0f) {}

    virtual uint32_t getOutputSize() { return this->outputSize; }

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

    virtual uint32_t getParameterCount() const { return 0; }

    virtual Vector<float> calculateError(Layer* previous, const Vector<float> prevError) = 0;

    virtual ~Layer() = default;
};

