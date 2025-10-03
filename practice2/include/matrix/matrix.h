#pragma once
#include "matrix/amatrix.h"

namespace my_math_lib {
template <typename T>
class Matrix : public AMatrix<T> {
public:
    Matrix(size_t rows, size_t cols) : AMatrix<T>(rows, cols) {
        this->data_ = VectorPtr<VectorPtr<T>>(new Vector<VectorPtr<T>>(rows));
        for (size_t i = 0; i < rows; ++i) {
            this->data_->operator[](i) = VectorPtr<T>(new Vector<T>(cols));
        }
    }
};
}  // namespace my_math_lib