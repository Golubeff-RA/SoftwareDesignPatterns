#pragma once

#include "idecorator.h"
#include "matrix/imatrix.h"

namespace my_math_lib {

template <typename T>
class TransposeDecorator : public IDecorator<T> {
public:
    TransposeDecorator(MatrixPtr<T> matrix) : IDecorator<T>(matrix) {}

    size_t Rows() const override { return this->matrix_->Columns(); }
    size_t Columns() const override { return this->matrix_->Rows(); }

    T operator[](size_t row, size_t col) const override {
        return (*this->matrix_)[col, row];
    }

    T& operator[](size_t row, size_t col) override {
        return (*this->matrix_)[col, row];
    }
};

}  // namespace my_math_lib