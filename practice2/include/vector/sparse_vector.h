#pragma once
#include <map>

#include "vector/ivector.h"

namespace my_math_lib {
template <typename T>
class SparseVector : public IVector<T> {
public:
    SparseVector(size_t size = 0) : size_(size) {}

    size_t Size() const override { return size_; }

    T operator[](size_t idx) const override {
        if (!data_.contains(idx)) {
            return T{};
        }
        return data_.at(idx);
    }

    T& operator[](size_t idx) override {
        if (!data_.contains(idx)) {
            data_.insert({idx, T{}});
        }

        return data_.at(idx);
    }

private:
    size_t size_;
    std::map<size_t, T> data_;
};
}  // namespace my_math_lib
