#pragma once
#include <memory>

#include "matrix/imatrix.h"
#include "vector/vector.h"

namespace my_math_lib {

template <typename T, typename Vec, typename VecOfVec>
class AMatrix : public IMatrix<T> {
private:
    VectorPtr<VectorPtr<T>> data_;
    size_t rows_ = 0;
    size_t cols_ = 0;

public:
    AMatrix(size_t rows = 0, size_t cols = 0) : rows_(rows), cols_(cols) {
        InitVec<VecOfVec, VectorPtr<VectorPtr<T>>>(rows, data_);
    }
        
    size_t Rows() const override { return rows_; }

    size_t Columns() const override { return Rows() > 0 ? cols_ : 0; }

    T operator()(size_t row, size_t col) const override {
        if (this->data_->operator[](row) == nullptr && row < this->rows_) {
            return T{};
        }
        return data_->operator[](row)->operator[](col);
    }

    T& operator()(size_t row, size_t col) override {
        if (this->data_->operator[](row) == nullptr && row < this->rows_) {
            InitVec<Vec, VectorPtr<T>>(this->cols_, this->data_->operator[](row));
        }
        return data_->operator[](row)->operator[](col);
    } 
};

template <typename Vec, typename VecPtr> 
void InitVec(size_t size, VecPtr& data){
    data = VecPtr(new Vec(size));
}


}  // namespace my_math_lib