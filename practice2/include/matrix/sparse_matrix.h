#pragma once

#include "matrix/amatrix.h"
#include "vector/sparse_vector.h"

namespace my_math_lib {
template <typename T>
class SparseMatrix : public AMatrix<T> {
public:
    SparseMatrix(size_t rows, size_t cols) : AMatrix<T>(rows, cols) {
        this->data_ = VectorPtr<VectorPtr<T>>(new SparseVector<VectorPtr<T>>(rows));
    }

    T& operator()(size_t row, size_t col) override {
        if (this->data_->operator[](row) == nullptr && row < this->rows_) {
            this->data_->operator[](row) = VectorPtr<T>(new SparseVector<T>(this->cols_));
        }
        return this->data_->operator[](row)->operator[](col);
    }
};
}  // namespace my_math_lib