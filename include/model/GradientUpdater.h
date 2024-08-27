#pragma once

#include <vector>

class GradientUpdater {

   public:
    virtual void init(int networkParameterCount) {}

    virtual void applyUpdater(std::vector<float>& parameters,
                              const std::vector<float>& gradient) = 0;

    virtual bool shouldUpdate(int epoch, int example) { return true; }
};
