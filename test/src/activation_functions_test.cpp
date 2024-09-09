#include <gtest/gtest.h>
#include "model/activationFunction.h"
#include "test_util.h"
#include "math/Vector.h"

TEST(NNTests, RELU) {
    Vector<float> inputs = {-999.0, -1.0, 0, 1.0, 2.0, 999.0};
    Vector<float> outputs = {0, 0, 0, 1.0, 2.0, 999.0};

    Vector<float> res = apply(inputs, ActivationFunction::RELU);
    EXPECT_VECTOR_EQ(res, outputs);
}
