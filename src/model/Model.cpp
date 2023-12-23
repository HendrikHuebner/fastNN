//
// Created by hhuebner on 12/19/23.
//

#include "model/Layer.h"
#include "model/costFunction.h"
#include "model/GradientUpdater.h"
#include "model/gradientDescent.h"
#include "model/DenseLayer.h"

class Model {

private:
    std::mt19937 rand;
    std::vector<Layer*> layers;
    CostFunction cost;
    std::unique_ptr<GradientUpdater> gradientUpdater;
    int parameterCount = 0;

public:

    Model() {

    }
    
    void init() {
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
    Vector propagateData(const Vector data, const int layerIndex) {
        if(layerIndex >= this->layers.size()) {
            return data;
        } else {
            this->layers[layerIndex]->processInput(data);
            return propagateData(this->layers[layerIndex]->getActivationVec(), layerIndex + 1);
        }
    }

    float determineCost(Vector networkOutput, Vector expected) {
        return applyCostFunction(this->cost, networkOutput, expected);
    }

    /**
     * Uses gradient descent and backpropagation to update the weights and biases in this network.
     */
     void updateParameters(Vector input, Vector output, Vector expected) {
        Vector nablaCost = applyCostDerivative(this->cost, output, expected);

        std::vector<Vector> error = calculateError(this->layers, nablaCost);
        std::vector<Vector> biasGradient = error;
        std::vector<Matrix*> weightGradient = calcWeightGradient(error, this->layers, input);

        for(int i = 0; i < this->layers.size(); i++) {
            Layer* layer = this->layers[i];

            if (DenseLayer* dense = dynamic_cast<DenseLayer*>(layer)) {
                std::vector<float>& weights = dense->getWeights()->array();
                std::vector<float>& biases = dense->getBiases().array();

                this->gradientUpdater->applyUpdater(weights, weightGradient[i]->array());
                this->gradientUpdater->applyUpdater(biases, biasGradient[i].array());
            }
        }
    }
};
