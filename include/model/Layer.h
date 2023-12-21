//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_LAYER_H
#define FASTNN_LAYER_H


#include <random>
#include "math/Vector.h"

class Layer {
public:
    Layer() {}

    virtual Vector processInput(const Vector& inputs) = 0;

    virtual void init(std::mt19937& rand) = 0;

    virtual int getParameterCount() const {
        return 0;
    }

    virtual std::vector<float> getParameters() const;

    virtual void setParameters(const std::vector<float>& floats);

    virtual ~Layer() = default;
};


#endif //FASTNN_LAYER_H
