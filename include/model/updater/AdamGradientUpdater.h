//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_ADAMGRADIENTUPDATER_H
#define FASTNN_ADAMGRADIENTUPDATER_H

#include <vector>
#include "model/GradientUpdater.h"

struct AdamUpdaterConfig {
    float alpha;
    float beta1;
    float beta2;
    float epsilon;
};

const struct AdamUpdaterConfig DEFAULT_CFG = {0.001F, 0.9F, 0.99F, 0.00000001F};

class AdamGradientUpdater : public GradientUpdater {

   private:
    const struct AdamUpdaterConfig config;
    std::vector<float> prevMoment;
    std::vector<float> prevVariance;

   public:
    AdamGradientUpdater(const struct AdamUpdaterConfig config) : config(config) {}

    void init(int networkParameterCount) override {
        prevMoment.resize(networkParameterCount);
        prevVariance.resize(networkParameterCount);
    }

    void applyUpdater(std::vector<float>& parameters, const std::vector<float>& gradient) override;
};

#endif  //FASTNN_ADAMGRADIENTUPDATER_H
