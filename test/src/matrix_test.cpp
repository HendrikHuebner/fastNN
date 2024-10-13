#include "math/Matrix.h"
#include <gtest/gtest.h>
#include "test_util.h"

TEST_EACH_FP_TYPE(MathTests, MatrixAdd) {
    Matrix<T> m0(5, 5, (T)0.0);
    Matrix<T> m1(5, 5, (T)1.0);
    Matrix<T> m2(5, 5, (T)2.0);
    Matrix<T> m3(5, 5, (T)3.0);

    EXPECT_MATRIX_EQ(m1 + m0 + m1 + m0, m2);
    EXPECT_MATRIX_EQ(m1 + m2, m3);
    EXPECT_MATRIX_EQ(m1 - m2 + m3 - m0, m2);
    EXPECT_MATRIX_EQ(m1 - m1, m0);
}

TEST_EACH_FP_TYPE(MathTests, SquareMatrixMul) {
    Matrix<T> id_3 = Matrix<T>::ident(3);
    Matrix<T> m0(3, 3, (T)0.0);
    Matrix<T> m1(3, 3, (T)1.0);
    Matrix<T> m3(3, 3, (T)3.0);

    T* d = new T[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<T> m4(3, 3, d);

    T* d2 = new T[]{30, 36, 42, 66, 81, 96, 102, 126, 150};

    Matrix<T> m5(3, 3, d2);
    
    EXPECT_MATRIX_EQ(id_3 * m3 * id_3 * id_3, m3);
    EXPECT_MATRIX_EQ(id_3 * m1 * id_3, m1);

    EXPECT_MATRIX_EQ(m3 * m3 * m3 * m0 * m3 * m1, m0);
    EXPECT_MATRIX_EQ(m1 * m1, m3);

    EXPECT_MATRIX_EQ(m4 * m4, m5);
}

TEST_EACH_FP_TYPE(MathTests, NonSquareMatrixMul) {
    T* a = new T[]{1, 2, 3, 4, 5, 6};
    Matrix<T> A(3, 2, a);

    T* b = new T[]{1, 2, 2, 1, 3, 2};
    Matrix<T> B(2, 3, b);

    T* c = new T[]{14, 10, 32, 25};
    Matrix<T> C(2, 2, c);

    T* a2 = new T[]{1, 2, 3, 4};
    Matrix<T> A2(1, 4, a2);

    T* b2 = new T[]{1, 2, 1, 2};
    Matrix<T> B2(4, 1, b2);

    T* c2 = new T[]{1, 2, 1, 2, 2, 4, 2, 4, 3, 6, 3, 6, 4, 8, 4, 8};
    Matrix<T> C2(4, 4, c2);

    T* c3 = new T[]{16};
    Matrix<T> C3(1, 1, c3);

    EXPECT_MATRIX_EQ(A * B, C);
    EXPECT_MATRIX_EQ(A2 * B2, C2);
    EXPECT_MATRIX_EQ(B2 * A2, C3);
}

TEST_EACH_FP_TYPE(MathTests, Transpose) {
    T* a = new T[]{1, 2, 3, 4, 5, 6};
    Matrix<T> A(3, 2, a);

    T* b = new T[]{1, 4, 2, 5, 3, 6};
    Matrix<T> B(2, 3, b);

    T* a2 = new T[]{1, 2, 3, 4};
    Matrix<T> A2(1, 4, a2); 

    T* b2 = new T[]{1, 2, 3, 4};
    Matrix<T> B2(4, 1, b2);

    Matrix<T> C(2, 3);
    Matrix<T> C2(4, 1);

    A.transpose(C);
    A2.transpose(C2);

    EXPECT_MATRIX_EQ(C, B);
    EXPECT_MATRIX_EQ(C2, B2);

}
