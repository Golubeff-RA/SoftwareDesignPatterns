#pragma once
#include <numeric>
#include <utility>
#include <vector>

#include "idecorator.h"

namespace my_math_lib {
template <typename T>
class SwapDecorator : public IDecorator<T> {
public:
    SwapDecorator(MatrixPtr<T> matrix)
        : IDecorator<T>(matrix),
          rows_permutation(matrix->Rows(), 0),
          cols_permutation(matrix->Columns(), 0) {
        Repare();
    }

    void SwapRows(size_t i, size_t j) {
        std::swap(rows_permutation[i], rows_permutation[j]);
    }

    void SwapColumns(size_t i, size_t j) {
        std::swap(cols_permutation[i], cols_permutation[j]);
    }

    void Repare() {
        std::iota(rows_permutation.begin(), rows_permutation.end(), 0);
        std::iota(cols_permutation.begin(), cols_permutation.end(), 0);
    }

    size_t Rows() const override { return this->matrix_.get()->Rows(); }

    size_t Columns() const override { return this->matrix_.get()->Columns(); }

    T operator[](size_t row, size_t col) const override {
        auto indexes = ProcessIndexes(row, col);
        return (*this->matrix_)[indexes.first, indexes.second];
    }

    T& operator[](size_t row, size_t col) override {
        auto indexes = ProcessIndexes(row, col);
        return (*this->matrix_)[indexes.first, indexes.second];
    }

private:
    std::pair<size_t, size_t> ProcessIndexes(size_t row, size_t col) const {
        return {rows_permutation[row], cols_permutation[col]};
    }

    std::vector<size_t> rows_permutation;
    std::vector<size_t> cols_permutation;
};
}  // namespace my_math_lib