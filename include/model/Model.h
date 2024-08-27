#pragma once

#include <memory>
#include <random>
#include "model/GradientUpdater.h"
#include "model/Layer.h"
#include "model/costFunction.h"

class Model {
   private:
    std::mt19937 rand;
    std::vector<Layer*> layers;
    CostFunction cost;
    std::unique_ptr<GradientUpdater> gradientUpdater;
    int parameterCount = 0;

   public:
    void init();

    /**
     * Recursively feeds data through neural network
     *
     * @param data
     * @param layerIndex
     * @return network output
     */
    Vector<float> propagateData(const Vector<float> data, const int layerIndex);

    /**
     * Uses gradient descent and backpropagation to update the weights and biases in this network.
     */
    void updateParameters(Vector<float> input, Vector<float> output, Vector<float> expected);

    /**
     * Calculates the cost from the expected output and the observed output
     *
     * @param networkOutput
     * @param expected
     * @return cost value
     */
    float determineCost(Vector<float> networkOutput, Vector<float> expected);
};
