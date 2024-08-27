#include "math/Matrix.h"
#include <gtest/gtest.h>
#include "test_util.h"

TEST_EACH_FP_TYPE(MatrixAddTest, BasicAssertions) {
    Matrix<T> id_5 = Matrix<T>::ident(5);
    Matrix<T> m1(5, 5, (T)1.0);
    Matrix<T> m2(5, 5, (T)2.0);
    Matrix<T> m3(5, 5, (T)3.0);

    
}

TEST_EACH_FP_TYPE(MatrixMulTest, BasicAssertions) {
    Matrix<T> id_3 = Matrix<T>::ident(3);
    Matrix<T> m0(3, 3, (T)0.0);
    Matrix<T> m1(3, 3, (T)1.0);
    Matrix<T> m3(3, 3, (T)3.0);

    T *d = new T[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<T> m4(3, 3, d);

    T *d2 = new T[]{30, 36, 42, 66, 81, 96, 102, 126, 150};
    Matrix<T> m5(3, 3, d2);

    EXPECT_MATRIX_EQ(id_3 * m3 * id_3 * id_3, m3);
    EXPECT_MATRIX_EQ(id_3 * m1 * id_3, m1);
    EXPECT_MATRIX_EQ(m3 * m3 * m3 * m0 * m3 * m1, m0);
    EXPECT_MATRIX_EQ(m1 * m1, m3);

    EXPECT_MATRIX_EQ(m4 * m4, m5);
}

TEST_EACH_FP_TYPE(MatrixVecTest, BasicAssertions) {

}
