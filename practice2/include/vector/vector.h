#pragma once

#include <vector>

#include "vector/ivector.h"
namespace my_math_lib {
template <typename T>
class Vector : public IVector<T> {
public:
    Vector(size_t size = 0) { data_.resize(size, T{}); }

    size_t Size() const override { return data_.size(); }

    T operator[](size_t idx) const override { return data_.at(idx); }

    T& operator[](size_t idx) override { return data_.at(idx); }

private:
    std::vector<T> data_;
};

}  // namespace my_math_lib
