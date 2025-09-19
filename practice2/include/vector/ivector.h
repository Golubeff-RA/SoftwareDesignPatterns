#pragma once

#include "vector/ivector.h"

namespace my_math_lib {
template <typename T>
class IVector {
public:
    virtual size_t Size() const = 0;
    virtual T operator[](size_t idx) const = 0;
    virtual T& operator[](size_t idx) = 0;
    virtual ~IVector() = default;
};
}  // namespace my_math_lib
