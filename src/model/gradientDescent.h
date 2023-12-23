//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_GRADIENTDESCENT_H
#define FASTNN_GRADIENTDESCENT_H


#include "model/Layer.h"
#include "math/Matrix.h"

/**
 * Calculates the errors at each layer.
 *
 * @tparam LAYER_COUNT
 * @param layers
 * @param nablaCost
 * @return array of error vectors
 */
std::vector<Vector> calculateError(const std::vector<Layer*> layers, const Vector& nablaCost);


/**
 * Calculate the gradient at the given index and layer
 * @param layer
 * @param index
 * @param prevActivation
 * @param errors
 * @return Gradient Matrix
 */
Matrix* calcWeightGradientAt(Layer* layer, int index, const Vector& prevActivation, const std::vector<Vector*>& errors);


/**
 * Calculates dC/dw by multiplying the error with the activation of the neuron of first layer the weight is connected to
 *
 * @param errors
 * @param layers
 * @param input
 * @return
 */
std::vector<Matrix*> weightGradient(const std::vector<Vector*> errors, const std::vector<Layer*>& layers, const Vector& input);

#endif //FASTNN_GRADIENTDESCENT_H
