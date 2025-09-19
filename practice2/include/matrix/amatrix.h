#pragma once
#include <memory>

#include "matrix/imatrix.h"
#include "vector/vector.h"

namespace my_math_lib {
template <typename T>
class AMatrix : public IMatrix<T> {
protected:
    std::shared_ptr<IVector<std::shared_ptr<IVector<T>>>> data_;

public:
    size_t Rows() const override { return data_->Size(); }

    size_t Columns() const override { return Rows() > 0 ? data_->operator[](0)->Size() : 0; }

    T operator()(size_t row, size_t col) const override {
        return data_->operator[](row)->operator[](col);
    }

    T& operator()(size_t row, size_t col) override {
        return data_->operator[](row)->operator[](col);
    }
};
}  // namespace my_math_lib