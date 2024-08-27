//
// Created by hhuebner on 12/21/23.
//

#include "model/updater/AdamGradientUpdater.h"
#include <cmath>

void AdamGradientUpdater::applyUpdater(std::vector<float>& parameters,
                                       const std::vector<float>& gradient) {
    for (size_t i = 0; i < parameters.size(); i++) {
        prevMoment[i] = (prevMoment[i] * config.beta1 + (1.0F - config.beta1) * gradient[i]);
        prevVariance[i] =
            (prevVariance[i] * config.beta2 + (1.0F - config.beta2) * gradient[i] * gradient[i]);
        float mHat = prevMoment[i] / (1.0F - config.beta1);
        float vHat = prevVariance[i] / (1.0F - config.beta2);
        parameters[i] -= config.alpha * mHat / (std::sqrt(vHat) + config.epsilon);
    }
}
