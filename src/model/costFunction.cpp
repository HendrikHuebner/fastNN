//
// Created by hhuebner on 12/20/23.
//

#include <cmath>
#include "math/Vector.h"
#include "model/costFunction.h"


float quadratic(const Vector& output, const Vector& expected) {
    double sum = 0;
    for (size_t i = 0; i < output.size(); i++) {
        sum += std::pow(expected[i] - output[i], 2);
    }

    return static_cast<float>(sum) / 2;
}

Vector nablaQuadratic(const Vector& output, const Vector& expected) {
    return output.sub(expected);
}

float kullbackLeibler(const Vector& output, const Vector& expected) {
    double sum = 0;
    for (size_t i = 0; i < output.size(); i++) {
        sum += expected[i] * std::log(expected[i] / output[i]);
    }
    return static_cast<float>(sum) / 2;
}

Vector nablaKullbackLeibler(const Vector& output, const Vector& expected) {
    return expected.div(output).scale(-1.0);
}

float crossEntropy(const Vector& output, const Vector& expected) {
    double sum = 0;
    for (size_t i = 0; i < output.size(); i++) {
        sum -= expected[i] * std::log(output[i]) + (1 - expected[i]) * std::log(1 - output[i]);
    }
    return static_cast<float>(sum);
}

Vector nablaCrossEntropy(const Vector& output, const Vector& expected) {
    return output.sub(expected).div(output.sub(output.mul(output)).clamp(0.000001F, 100000.0F));
}

float applyCostFunction(CostFunction costFunction, const Vector& output, const Vector& expected) {
    switch (costFunction) {
        case QUADRATIC:
            return quadratic(output, expected);
        case CROSS_ENTROPY:
            return crossEntropy(output, expected);
        case KULLBACK_LEIBLER:
            return kullbackLeibler(output, expected);
    }
}

Vector applyCostDerivative(CostFunction costFunction, const Vector& output, const Vector& expected) {
    switch (costFunction) {
        case QUADRATIC:
            return nablaQuadratic(output, expected);
        case CROSS_ENTROPY:
            return nablaCrossEntropy(output, expected);
        case KULLBACK_LEIBLER:
            return nablaKullbackLeibler(output, expected);
    }
}
