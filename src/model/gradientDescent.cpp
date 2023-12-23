//
// Created by hhuebner on 12/21/23.
//

#include <memory>
#include "gradientDescent.h"
#include "vector"
#include "math/Vector.h"
#include "model/Layer.h"
#include "math/Matrix.h"

std::vector<Vector> calculateError(const std::vector<Layer*> layers, const Vector& nablaCost) {

    std::vector<Vector> errors;

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


Matrix* calcWeightGradientAt(Layer* layer, int index, const Vector& prevActivation, const std::vector<Vector*>& errors) {
    auto matrix = new Matrix(prevActivation.size(), layer->getOutputSize());
    const Vector* error = errors[index];

    for (int i = 0; i < matrix->getWidth(); i++) {
        for (int j = 0; j < matrix->getHeight(); j++) {
            matrix->set(i, j, (*error)[j] * prevActivation[i]);
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
std::vector<Matrix*> weightGradient(const std::vector<Vector*> errors, const std::vector<Layer*>& layers, const Vector& input) {
    std::vector<Matrix*> grad;
    grad.reserve(layers.size());

    Vector previousActivation = input;

    for (size_t i = 0; i < layers.size(); i++) {
        Layer* layer = layers[i];
        Matrix* gradient = calcWeightGradientAt(layer, i, previousActivation, errors);
        grad[i] = gradient;

        previousActivation = layer->getActivationVec();
    }

    return grad;
}
