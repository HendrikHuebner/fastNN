//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_ADAMGRADIENTUPDATER_H
#define FASTNN_ADAMGRADIENTUPDATER_H

#include <vector>
#include "model/GradientUpdater.h"

struct SGDUpdaterConfig {
    float learningRate;
    int batchSize;
};

class SGDGradientUpdater : public GradientUpdater {

   private:
    const struct SGDUpdaterConfig config;
    std::vector<float> prevMoment;
    std::vector<float> prevVariance;

   public:
    SGDGradientUpdater(const struct SGDUpdaterConfig config) : config(config) {}

    void init(int networkParameterCount) override {
        prevMoment.resize(networkParameterCount);
        prevVariance.resize(networkParameterCount);
    }

    void applyUpdater(std::vector<float>& parameters, const std::vector<float>& gradient) override {
        for (int i = 0; i < gradient.size(); i++) {
            parameters[i] -= gradient[i] * this->config.learningRate;
        }
    }

    bool shouldUpdate(int epoch, int example) override {
        return example % this->config.batchSize == 0;
    }
};

#endif  //FASTNN_ADAMGRADIENTUPDATER_H
