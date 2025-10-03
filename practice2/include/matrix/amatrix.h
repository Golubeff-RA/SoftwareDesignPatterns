#pragma once
#include <memory>

#include "matrix/imatrix.h"
#include "vector/vector.h"

namespace my_math_lib {
template <typename T>
class AMatrix : public IMatrix<T> {
protected:
    VectorPtr<VectorPtr<T>> data_;
    size_t rows_ = 0;
    size_t cols_ = 0;

public:
    AMatrix(size_t rows = 0, size_t cols = 0) : rows_(rows), cols_(cols) {}

    size_t Rows() const override { return rows_; }

    size_t Columns() const override { return Rows() > 0 ? cols_ : 0; }

    T operator()(size_t row, size_t col) const override {
        if (this->data_->operator[](row) == nullptr) {
            return T{};
        }
        return data_->operator[](row)->operator[](col);
    }

    T& operator()(size_t row, size_t col) override {
        return data_->operator[](row)->operator[](col);
    }
};

template <typename T, typename Vec, typename VecOfVec>
void InitVecOfVecs(size_t rows, size_t cols, VectorPtr<VectorPtr<T>>& data_) {
    data_ = VectorPtr<VectorPtr<T>>(new VecOfVec(rows));
    for (size_t i = 0; i < rows; ++i) {
        data_->operator[](i) = VectorPtr<T>(new Vec(cols));
    }
}

}  // namespace my_math_lib