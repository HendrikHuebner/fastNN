//
// Created by hhuebner on 12/19/23.
//

#ifndef FASTNN_MODEL_H
#define FASTNN_MODEL_H


#include "math/Vector.h"

class Model {

};

enum InitializationFunction {
    UNIFORM,
    XAVIER,
    GAUSSIAN,
    ZEROS,
    ONES
};


Vector propagateData(const Vector data, const int layerIndex);




#endif //FASTNN_MODEL_H
