#pragma once
#include "matrix/amatrix.h"

namespace my_math_lib {
template <typename T>
class Matrix : public AMatrix<T, Vector<T>, Vector<VectorPtr<T>>> {
public:
    Matrix(size_t rows, size_t cols) : AMatrix<T, Vector<T>, Vector<VectorPtr<T>>>(rows, cols) {
    }
};
}  // namespace my_math_lib