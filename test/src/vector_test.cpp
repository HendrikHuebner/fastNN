#include "math/Vector.h"
#include <gtest/gtest.h>
#include "test_util.h"
#include <float.h>

using namespace std;

TEST_EACH_FP_TYPE(VectorAdditionTest, BasicAssertions) {
    Vector<T> v0(5);
    Vector<T> v1(5, 1.0);
    Vector<T> v2(5, 2.0);
    Vector<T> v3(5, 3.0);

    Vector<T> w0(500);
    Vector<T> w1(500, 1.0);
    Vector<T> w2(500, 2.0);
    Vector<T> w3(500, 3.0);

    EXPECT_VECTOR_EQ(v1 + v2, v3);
    EXPECT_VECTOR_EQ(v3 - v2, v1);
    EXPECT_VECTOR_EQ(v2 - v1 + v0, v1);
    EXPECT_VECTOR_EQ(v1 - v3 + v2, v0 + v0);

    // in-place
    v2.add(v0, v1);
    EXPECT_VECTOR_EQ(v0, v3);
    v0.sub(v0, v1);
    v0.sub(v0, v1);
    EXPECT_VECTOR_EQ(v0, v1);

    EXPECT_VECTOR_EQ(w1 + w2, w3);
    EXPECT_VECTOR_EQ(w3 - w2, w1);
    EXPECT_VECTOR_EQ(w2 - w1 + w0, w1);
    EXPECT_VECTOR_EQ(w1 - w3 + w2, w0 + w0);

    // in-place
    w2.add(w0, w1);
    EXPECT_VECTOR_EQ(w0, w3);
    w0.sub(w0, w1);
    w0.sub(w0, w1);
    EXPECT_VECTOR_EQ(w0, w1);
}
