#pragma once

#include "matrix/amatrix.h"
#include "vector/sparse_vector.h"

namespace my_math_lib {
template <typename T>
class SparseMatrix : public AMatrix<T, SparseVector<T>, SparseVector<VectorPtr<T>>> {
public:
    SparseMatrix(size_t rows, size_t cols) : AMatrix<T, SparseVector<T>, SparseVector<VectorPtr<T>>>(rows, cols) {
    }
};
}  // namespace my_math_lib