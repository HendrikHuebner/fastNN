//
// Created by hhuebner on 12/19/23.
//

#ifndef FASTNN_MODEL_H
#define FASTNN_MODEL_H


#include "model/costFunction.h"
#include "model/GradientUpdater.h"
#include "model/gradientDescent.h"
#include "model/DenseLayer.h"
#include <iostream>


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
    Vector propagateData(const Vector data, const int layerIndex);

    /**
     * Uses gradient descent and backpropagation to update the weights and biases in this network.
     */
    void updateParameters(Vector input, Vector output, Vector expected);

    /**
     * Calculates the cost from the expected output and the observed output
     *
     * @param networkOutput
     * @param expected
     * @return cost value
     */
    float determineCost(Vector networkOutput, Vector expected);

Vector propagateData(const Vector data, const int layerIndex);


};


#endif //FASTNN_MODEL_H
