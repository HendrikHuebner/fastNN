//
// Created by hhuebner on 12/21/23.
//

#ifndef FASTNN_GRADIENTUPDATER_H
#define FASTNN_GRADIENTUPDATER_H

class GradientUpdater {

public:

    virtual void init(int networkParameterCount) {}

    virtual void applyUpdater(std::vector<float> &parameters, const std::vector<float> &gradient) = 0;

    virtual bool shouldUpdate(int epoch, int example) {
        return true;
    }
};

#endif //FASTNN_GRADIENTUPDATER_H
