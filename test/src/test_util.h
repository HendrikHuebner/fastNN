#include <gtest/gtest.h>

#define ASSERT_VECTOR_SIZE_EQ(v, e) ASSERT_EQ((v).length(), (e).length())

#define EXPECT_VECTOR_EQ(v, e)               \
    ASSERT_VECTOR_SIZE_EQ(v, e);             \
    for (int i = 0; i < (e).length(); i++) { \
        EXPECT_EQ((v)[i], (e)[i]);           \
    }

#define ASSERT_MATRIX_DIMS_EQ(m, e)            \
    ASSERT_EQ((m).getWidth(), (e).getWidth()); \
    ASSERT_EQ((m).getHeight(), (e).getHeight())

#define EXPECT_MATRIX_EQ(m, e)                \
    ASSERT_MATRIX_DIMS_EQ(m, e);              \
    for (int i = 0; i < (e).getSize(); i++) { \
        EXPECT_EQ((m)[i], (e)[i]);            \
    }

#define TEST_EACH_FP_TYPE(name, type)      \
    template <typename Type>               \
    void eachfp_test_body_##name(void);    \
    TEST(f32_##name, type) {               \
        eachfp_test_body_##name<float>();  \
    }                                      \
    TEST(f64_##name, type) {               \
        eachfp_test_body_##name<double>(); \
    }                                      \
    template <typename T>                  \
    void eachfp_test_body_##name()\
