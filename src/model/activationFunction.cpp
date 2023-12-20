//
// Created by hhuebner on 12/20/23.
//
#include "model/activationFunction.h"
#include <cmath>


inline Vector relu(Vector& vec) {
    Vector out = Vector(vec.size(), 0.0f);

    for(int i = 0; i < vec.size(); i++) {
        if(vec.data[i] > 0) {
            out.data[i] =  vec.data[i];
        }
    }

    return out;
}

inline Vector dRelu(Vector& vec) {
    Vector out = Vector(vec.size(), 0.0f);

    for(int i = 0; i < vec.size(); i++) {

        if(vec.data[i] > 0) {
            out.data[i] = 1;
        }
    }

    return out;
}

inline Vector sigmoid(Vector& vec) {
    Vector out = Vector(vec.size(), 0);

    for(int i = 0; i < vec.size(); i++) {
        out.data[i] = (float) (1/(1 + exp(-vec.data[i])));
    }

    return out;
}

inline Vector dSigmoid(Vector& vec) {
    Vector out = sigmoid(vec);

    Vector result = Vector(vec.size(), 1.0F);
    return out.mul(result).sub(out);
}

inline Vector softmax(Vector& vec) {
    Vector out = Vector(vec.size(), 0.0f);
    float max = vec.max();
    double divisor = 0;

    for(int i = 0; i < vec.size(); i++) {
        out.data[i] = (float) exp(vec.data[i] - max);
        divisor += out.data[i];
    }

    out = out.scale(1.0 / divisor);

    return out;
}

inline Vector dSoftmax(Vector& vec) {
    Vector out = softmax(vec);

    Vector result = Vector(vec.size(), 1.0F).sub(out);
    return out.mul(result);
}

Vector apply(Vector &vector, ActivationFunction f) {
    switch (f) {
        case RELU:
            return relu(vector);
        case SIGMOID:
            return sigmoid(vector);
        case SOFTMAX:
            return softmax(vector);
    };
}

Vector applyDerivative(Vector& vector, ActivationFunction f) {
    switch (f) {
        case RELU:
            return dRelu(vector);
        case SIGMOID:
            return dSigmoid(vector);
        case SOFTMAX:
            return dSoftmax(vector);
    };
}
