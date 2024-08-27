#pragma once

#include "math/Matrix.h"
#include "model/Layer.h"

/**
 * Calculates the errors at each layer.
 *
 * @tparam LAYER_COUNT
 * @param layers
 * @param nablaCost
 * @return array of error vectors
 */
std::vector<Vector<float>> calculateError(const std::vector<Layer*> layers,
                                          const Vector<float>& nablaCost);

/**
 * Calculate the gradient at the given index and layer
 * @param layer
 * @param index
 * @param prevActivation
 * @param errors
 * @return Gradient Matrix
 */
Matrix<float>* calcWeightGradientAt(Layer* layer, int index, const Vector<float>& prevActivation,
                                    const std::vector<Vector<float>>& errors);

/**
 * Calculates dC/dw by multiplying the error with the activation of the neuron of first layer the weight is connected to
 *
 * @param errors
 * @param layers
 * @param input
 * @return
 */
std::vector<Matrix<float>*> calcWeightGradient(const std::vector<Vector<float>> errors,
                                               const std::vector<Layer*>& layers,
                                               const Vector<float>& input);
