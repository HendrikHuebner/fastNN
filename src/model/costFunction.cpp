//
// Created by hhuebner on 12/20/23.
//

#include <cmath>
#include <stdexcept>
#include "math/Vector.h"
#include "model/costFunction.h"


float quadratic(const Vector<float>& output, const Vector<float>& expected) {
    double sum = 0;
    for (size_t i = 0; i < output.length(); i++) {
        sum += std::pow(expected[i] - output[i], 2);
    }

    return static_cast<float>(sum) / 2;
}

Vector<float> nablaQuadratic(const Vector<float>& output, const Vector<float>& expected) {
    return output.sub(expected);
}

float kullbackLeibler(const Vector<float>& output, const Vector<float>& expected) {
    double sum = 0;
    for (size_t i = 0; i < output.length(); i++) {
        sum += expected[i] * std::log(expected[i] / output[i]);
    }
    return static_cast<float>(sum) / 2;
}

Vector<float> nablaKullbackLeibler(const Vector<float>& output, const Vector<float>& expected) {
    return expected.div(output).mul(-1.0);
}

float crossEntropy(const Vector<float>& output, const Vector<float>& expected) {
    double sum = 0;
    for (size_t i = 0; i < output.length(); i++) {
        sum -= expected[i] * std::log(output[i]) + (1 - expected[i]) * std::log(1 - output[i]);
    }
    return static_cast<float>(sum);
}

Vector<float> nablaCrossEntropy(const Vector<float>& output, const Vector<float>& expected) {
    return output.sub(expected).div(output.sub(output.mul(output)).clamp(0.000001F, 100000.0F));
}

float applyCostFunction(CostFunction costFunction, const Vector<float>& output, const Vector<float>& expected) {
    switch (costFunction) {
        case QUADRATIC:
            return quadratic(output, expected);
        case CROSS_ENTROPY:
            return crossEntropy(output, expected);
        case KULLBACK_LEIBLER:
            return kullbackLeibler(output, expected);

        default:
            throw std::invalid_argument("Unknown Cost Function");
    }
}

Vector<float> applyCostDerivative(CostFunction costFunction, const Vector<float>& output, const Vector<float>& expected) {
    switch (costFunction) {
        case QUADRATIC:
            return nablaQuadratic(output, expected);
        case CROSS_ENTROPY:
            return nablaCrossEntropy(output, expected);
        case KULLBACK_LEIBLER:
            return nablaKullbackLeibler(output, expected);

        default:
            throw std::invalid_argument("Unknown Cost Function");
    }
}
