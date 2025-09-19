#pragma once

#include "matrix/amatrix.h"
#include "vector/sparse_vector.h"

namespace my_math_lib {
template <typename T>
class SparseMatrix : public AMatrix<T> {
public:
    SparseMatrix(size_t rows, size_t cols) {
        this->data_ = std::shared_ptr<IVector<std::shared_ptr<IVector<T>>>>(
            new SparseVector<std::shared_ptr<IVector<T>>>(rows));
        for (size_t i = 0; i < rows; ++i) {
            this->data_->operator[](i) = std::shared_ptr<IVector<T>>(new SparseVector<T>(cols));
        }
    }
};
}  // namespace my_math_lib