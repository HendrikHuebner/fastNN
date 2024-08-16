//
// Created by hhuebner on 12/20/23.
//
#include "model/activationFunction.h"
#include <cmath>
#include <stdexcept>


inline Vector<float> relu(Vector<float>& vec) {
    Vector<float> out = Vector<float>(vec.length(), 0.0f);

    for(int i = 0; i < vec.length(); i++) {
        if(vec[i] > 0) {
            out[i] = vec[i];
        }
    }

    return out;
}

inline Vector<float> dRelu(Vector<float>& vec) {
    Vector<float> out = Vector<float>(vec.length(), 0.0f);

    for(int i = 0; i < vec.length(); i++) {

        if(vec[i] > 0) {
            out[i] = 1;
        }
    }

    return out;
}

inline Vector<float> sigmoid(Vector<float>& vec) {
    Vector<float> out = Vector<float>(vec.length(), 0);

    for(int i = 0; i < vec.length(); i++) {
        out[i] = (float) (1/(1 + std::exp(-vec[i])));
    }

    return out;
}

inline Vector<float> dSigmoid(Vector<float>& vec) {
    Vector<float> out = sigmoid(vec);

    Vector<float> result = Vector<float>(vec.length(), 1.0F);
    return out.mul(result).sub(out);
}

inline Vector<float> softmax(Vector<float>& vec) {
    Vector<float> out = Vector<float>(vec.length(), 0.0f);
    float max = vec.max();
    double divisor = 0;

    for(int i = 0; i < vec.length(); i++) {
        out[i] = (float) std::exp(vec[i] - max);
        divisor += out[i];
    }

    return out.mul(1.0 / divisor);
}

inline Vector<float> dSoftmax(Vector<float>& vec) {
    Vector<float> out = softmax(vec);

    Vector<float> result = Vector<float>(vec.length(), 1.0F).sub(out);
    return out.mul(result);
}

Vector<float> apply(Vector<float> &vector, ActivationFunction f) {
    switch (f) {
        case RELU:
            return relu(vector);
        case SIGMOID:
            return sigmoid(vector);
        case SOFTMAX:
            return softmax(vector);

        default:
            throw std::invalid_argument("Unknown Activation Function");
    }
}

Vector<float> applyDerivative(Vector<float>& vector, ActivationFunction f) {
    switch (f) {
        case RELU:
            return dRelu(vector);
        case SIGMOID:
            return dSigmoid(vector);
        case SOFTMAX:
            return dSoftmax(vector);

        default:
            throw std::invalid_argument("Unknown Activation Function");
    }
}
