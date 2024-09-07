#include "math/Vector.h"
#include <float.h>
#include <gtest/gtest.h>
#include "test_util.h"

using namespace std;

TEST_EACH_FP_TYPE(MathTests, VectorAdditionTest) {
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

TEST_EACH_FP_TYPE(MathTests, VectorMulTest) {
    Vector<T> v0(5);
    Vector<T> v1(5, 1.0);
    Vector<T> v2(5, 2.0);
    Vector<T> v4(5, 4.0);

    Vector<T> w0(500);
    Vector<T> w1(500, 1.0);
    Vector<T> w2(500, 2.0);
    Vector<T> w4(500, 4.0);

    EXPECT_VECTOR_EQ(v1 * v2, v2);
    EXPECT_VECTOR_EQ(v2 * v2, v4);
    EXPECT_VECTOR_EQ(v2 / v2, v1);
    EXPECT_VECTOR_EQ(v4 * v4 * v0, v0);
    EXPECT_VECTOR_EQ(v1 * v2 * v4 / v2, v4);

    // in-place
    v2.mul(v0, v2);
    EXPECT_VECTOR_EQ(v0, v4);
    v0.div(v0, v1);
    EXPECT_VECTOR_EQ(v0, v4);
    v0.div(v0, v2);
    EXPECT_VECTOR_EQ(v0, v2);

    EXPECT_VECTOR_EQ(w1 * w2, w2);
    EXPECT_VECTOR_EQ(w2 * w2, w4);
    EXPECT_VECTOR_EQ(w2 / w2, w1);
    EXPECT_VECTOR_EQ(w4 * w4 * w0, w0);
    EXPECT_VECTOR_EQ(w1 * w2 * w4 / w2, w4);

    // in-place
    w2.mul(w0, w2);
    EXPECT_VECTOR_EQ(w0, w4);
    w0.div(w0, w1);
    EXPECT_VECTOR_EQ(w0, w4);
    w0.div(w0, w2);
    EXPECT_VECTOR_EQ(w0, w2);
}

TEST_EACH_FP_TYPE(MathTests, VectorDotProdTest) {
    Vector<T> v2(5, 2.0);
    Vector<T> v3(5, 3.0);

    Vector<T> w2(500, 2.0);
    Vector<T> w3(500, 3.0);

    T v0 = v2.dot(v3);
    T v1 = v3.dot(v2);

    EXPECT_EQ(v0, (T)5 * 6.0);
    EXPECT_EQ(v1, (T)5 * 6.0);

    T w0 = w2.dot(w3);
    T w1 = w3.dot(w2);

    EXPECT_EQ(w0, (T)500 * 6.0);
    EXPECT_EQ(w1, (T)500 * 6.0);
}
