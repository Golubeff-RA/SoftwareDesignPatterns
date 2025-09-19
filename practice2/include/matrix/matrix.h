#pragma once
#include "matrix/amatrix.h"

namespace my_math_lib {
template <typename T>
class Matrix : public AMatrix<T> {
public:
    Matrix(size_t rows, size_t cols) {
        this->data_ = std::shared_ptr<IVector<std::shared_ptr<IVector<T>>>>(
            new Vector<std::shared_ptr<IVector<T>>>(rows));
        for (size_t i = 0; i < rows; ++i) {
            this->data_->operator[](i) = std::shared_ptr<IVector<T>>(new Vector<T>(cols));
        }
    }
};
}  // namespace my_math_lib