//
// Created by hhuebner on 12/21/23.
//
#pragma once

#include "model/gradientDescent.h"
#include "vector"
#include "math/Vector.h"
#include "model/Layer.h"
#include "math/Matrix.h"

std::vector<Vector<float>> calculateError(const std::vector<Layer*> layers, const Vector<float>& nablaCost) {

    std::vector<Vector<float>> errors;

    // Last layer
    int index = layers.size() - 1;

    // Backpropagation
    Layer* prev = nullptr;
    Vector prevError = nablaCost;

    while (index >= 0) {
        Layer* layer = layers[index];

        Vector error = layer->calculateError(prev, prevError);
        errors[index] = error;

        prevError = error;
        prev = layer;

        index--;
    }

    return errors;
}


Matrix<float>* calcWeightGradientAt(Layer* layer, int index, const Vector<float>& prevActivation, const std::vector<Vector<float>>& errors) {
    auto matrix = new Matrix<float>(prevActivation.length(), layer->getOutputSize());
    const Vector error = errors[index];

    for (int i = 0; i < matrix->getWidth(); i++) {
        for (int j = 0; j < matrix->getHeight(); j++) {
            matrix->set(i, j, error[j] * prevActivation[i]);
        }
    }

    return matrix;
}

/**
 * Calculates dC/dw by multiplying the error with the activation of the neuron of first layer the weight is connected to
 *
 * @param errors
 * @param layers
 * @param input
 * @return
 */
std::vector<Matrix<float>*> calcWeightGradient(const std::vector<Vector<float>> errors, const std::vector<Layer*>& layers, const Vector<float>& input) {
    std::vector<Matrix<float>*> grad;
    grad.reserve(layers.size());


    for (size_t i = 0; i < layers.size(); i++) {
        Vector<float> previousActivation = (i = 0) ? input : layers[i - 1]->getActivationVec();
        Matrix<float>* gradient = calcWeightGradientAt(layers[i], i, previousActivation, errors);
        grad[i] = gradient;
    }

    return grad;
}
