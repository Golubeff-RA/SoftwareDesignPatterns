#pragma once

#include <cstddef>
#include <list>
#include <memory>
#include <optional>

#include "matrix/imatrix.h"
#include "transpose_decorator.h"

namespace my_math_lib {

template <typename T>
class HorizontalGroup : public IMatrix<T> {
public:
    HorizontalGroup() {}

    void AddMatrix(MatrixPtr<T> matrix) { matrices_.push_back(matrix); }

    size_t Rows() const override {
        size_t max_rows = 0;
        for (const auto& matrix : matrices_) {
            max_rows = std::max(max_rows, matrix->Rows());
        }
        return max_rows;
    }

    size_t Columns() const override {
        size_t total_cols = 0;
        for (const auto& matrix : matrices_) {
            total_cols += matrix->Columns();
        }
        return total_cols;
    }

    T operator[](size_t row, size_t col) const override {
        auto idxs = FindMatrixAndCol(row, col);
        if (idxs.has_value()) {
            return (*(*idxs).first)[row, (*idxs).second];
        }

        return T{};
    }

    T& operator[](size_t row, size_t col) override {
        auto idxs = FindMatrixAndCol(row, col);
        if (idxs.has_value()) {
            return (*(*idxs).first)[row, (*idxs).second];
        }

        static T zero = T{};
        zero = T{};
        return zero;
    }

    std::list<std::pair<size_t, size_t>> GetMatricesSizes() {
        std::list<std::pair<size_t, size_t>> answer;
        for (auto matr : matrices_) {
            answer.push_back({matr->Rows(), matr->Columns()});
        }
        return answer;
    }

private:
    std::list<MatrixPtr<T>> matrices_;

    std::optional<std::pair<MatrixPtr<T>, size_t>> FindMatrixAndCol(
        size_t row, size_t col) const {
        if (row >= Rows() || col >= Columns()) {
            throw std::out_of_range("Matrix indices out of range");
        }

        size_t current_col = 0;
        for (auto matrix : matrices_) {
            size_t mat_cols = matrix->Columns();
            size_t mat_rows = matrix->Rows();

            if (col < current_col + mat_cols) {
                size_t local_col = col - current_col;
                if (row < mat_rows) {
                    return std::pair{matrix, local_col};
                }

                return std::nullopt;
            }
            current_col += mat_cols;
        }
        return std::nullopt;
    }
};

template <typename T>
class VerticalGroup : public IMatrix<T> {
public:
    VerticalGroup() {}
    void AddMatrix(MatrixPtr<T> matrix) {
        horizontal_group_->AddMatrix(
            std::make_shared<TransposeDecorator<T>>(matrix));
    }

    size_t Rows() const override { return transposed_->Rows(); }

    size_t Columns() const override { return transposed_->Columns(); }

    T operator[](size_t row, size_t col) const override {
        return (*transposed_)[row, col];
    }

    T& operator[](size_t row, size_t col) override {
        return (*transposed_)[row, col];
    }

    std::list<std::pair<size_t, size_t>> GetMatricesSizes() {
        return horizontal_group_->GetMatricesSizes();
    }

private:
    std::shared_ptr<HorizontalGroup<T>> horizontal_group_ =
        std::make_shared<HorizontalGroup<T>>();
    MatrixPtr<T> transposed_ =
        std::make_shared<TransposeDecorator<T>>(horizontal_group_);
};

}  // namespace my_math_lib