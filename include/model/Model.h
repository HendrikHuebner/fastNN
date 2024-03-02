//
// Created by hhuebner on 12/19/23.
//

#ifndef FASTNN_MODEL_H
#define FASTNN_MODEL_H


#include <iostream>

void hello() {
    std::cout << "Hello from fastNN!" << std::endl;
}

class Model {
public:

};

enum InitializationFunction {
    UNIFORM,
    XAVIER,
    GAUSSIAN,
    ZEROS,
    ONES
};




#endif //FASTNN_MODEL_H
