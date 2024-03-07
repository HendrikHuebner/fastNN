//
// Created by hhuebner on 3/3/24.
//

#include <cstdint>
#include <stdexcept>
#include "math/Matrix.h"


class Dense32 : public Matrix<float> {

public:
    Dense32(const uint32_t width, const uint32_t height) : Matrix<float>(width, height) {}

    void add(const Dense32& o, Dense32& result) const;

    void sub(const Dense32& o, Dense32& result) const;

    void mul(const Dense32& o, Dense32& result) const;

    void mul(const Vector<float>& o, Vector<float>& result) const;

    Matrix<float> transpose() const;
};