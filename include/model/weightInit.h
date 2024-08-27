#include <random>

//
// Created by hhuebner on 12/21/23.
//

enum WeightInit { UNIFORM, XAVIER, GAUSSIAN, ZEROS, ONES };

inline float initializeWeight(WeightInit weightInit, std::mt19937& random, int inputSize) {
    switch (weightInit) {
        case WeightInit::UNIFORM:
            return std::uniform_real_distribution<float>(-0.5F, 0.5F)(random);
        case WeightInit::XAVIER:
            return static_cast<float>(std::uniform_real_distribution<double>(-0.5, 0.5)(random) *
                                      2.0 / inputSize);
        case WeightInit::GAUSSIAN:
            return std::normal_distribution<float>(0.0F, 1.0F)(random);
        case WeightInit::ZEROS:
            return 0.0F;
        case WeightInit::ONES:
            return 1.0F;
    }

    return 0.0F;
}
