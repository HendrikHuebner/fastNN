#include <gtest/gtest.h>
#include <cstdint>

#define ASSERT_VECTOR_SIZE_EQ(v, e) ASSERT_EQ((v).length(), (e).length())

#define EXPECT_VECTOR_EQ(v, e)               \
    ASSERT_VECTOR_SIZE_EQ(v, e);             \
    for (size_t i = 0; i < (e).length(); i++) { \
        EXPECT_EQ((v)[i], (e)[i]);           \
    }

#define ASSERT_MATRIX_DIMS_EQ(m, e)            \
    ASSERT_EQ((m).getWidth(), (e).getWidth()); \
    ASSERT_EQ((m).getHeight(), (e).getHeight())

#define EXPECT_MATRIX_EQ(m, e)                \
    ASSERT_MATRIX_DIMS_EQ(m, e);              \
    for (size_t i = 0; i < (e).getSize(); i++) { \
        EXPECT_EQ((m)[i], (e)[i]);            \
    }

#define TEST_EACH_FP_TYPE(suite, name)            \
    template <typename Type>                      \
    void _testeachfptype_##suite_##name(void);    \
    TEST(suite, f32_##name) {                     \
        _testeachfptype_##suite_##name<float>();  \
    }                                             \
    TEST(suite, f64_##name) {                     \
        _testeachfptype_##suite_##name<double>(); \
    }                                             \
    template <typename T>                         \
    void _testeachfptype_##suite_##name()
