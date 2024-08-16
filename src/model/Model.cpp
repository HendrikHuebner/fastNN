//
// Created by hhuebner on 12/19/23.
//

#include "model/Model.h"
#include "math/Matrix.h"
#include "model/DenseLayer.h"
#include "model/gradientDescent.h"


void Model::init() {
    for(Layer* layer : this->layers) {
        layer->init(this->rand);
        this->parameterCount += layer->getParameterCount();
    }

    this->gradientUpdater->init(this->parameterCount);
}

/**
* Recursively feeds data through neural network
*
* @param data
* @param layerIndex
* @return network output
*/
Vector<float> Model::propagateData(const Vector<float> data, const int layerIndex) {
    if(layerIndex >= this->layers.size()) {
        return data;
    } else {
        this->layers[layerIndex]->processInput(data);
        return propagateData(this->layers[layerIndex]->getActivationVec(), layerIndex + 1);
    }
}

float Model::determineCost(Vector<float> networkOutput, Vector<float> expected) {
    return applyCostFunction(this->cost, networkOutput, expected);
}

void Model::updateParameters(Vector<float> input, Vector<float> output, Vector<float> expected) {
    Vector<float> nablaCost = applyCostDerivative(this->cost, output, expected);

    std::vector<Vector<float>> error = calculateError(this->layers, nablaCost);
    std::vector<Vector<float>> biasGradient = error;
    std::vector<Matrix<float>*> weightGradient = calcWeightGradient(error, this->layers, input);

    for(int i = 0; i < this->layers.size(); i++) {
        Layer* layer = this->layers[i];

        if (DenseLayer* dense = dynamic_cast<DenseLayer*>(layer)) {
            std::vector<float> weights = dense->getWeights()->toStdVector();
            std::vector<float> biases = dense->getBiases().toStdVector();

            this->gradientUpdater->applyUpdater(weights, weightGradient[i]->toStdVector());
            this->gradientUpdater->applyUpdater(biases, biasGradient[i].toStdVector());
        }
    }
}

void train(Model model, const std::vector<Vector<float>> features, const std::vector<Vector<float>> labels) {
    for(int i = 0; i < features.size(); i++ ) {
        Vector<float> output = model.propagateData(features[i], 0);

    }
}
