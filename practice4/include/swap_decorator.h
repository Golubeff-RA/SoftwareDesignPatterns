#pragma once
#include <utility>

#include "idecorator.h"
#include "random_generator/random_generator.h"

namespace my_math_lib {
template <typename T>
class SwapDecorator : public IDecorator<T> {
public:
    SwapDecorator(MatrixPtr<T> matrix) : IDecorator<T>(matrix) {}

    void RandomSwap() {
        RandomGenerator<size_t> gena;
        if (Columns() >= 2) {
            columns.first = gena.Generate(0, Columns() - 1);
            do {
                columns.second = gena.Generate(0, Columns() - 1);
            } while (columns.first == columns.second);
        }

        if (Rows() >= 2) {
            rows.first = gena.Generate(0, Rows() - 1);
            do {
                rows.second = gena.Generate(0, Rows() - 1);
            } while (rows.first == rows.second);
        }
    }

    void Repare() {
        columns = {0, 0};
        rows = {0, 0};
    }

    size_t Rows() const override { return this->matrix_.get()->Rows(); }

    size_t Columns() const override { return this->matrix_.get()->Columns(); }

    T operator[](size_t row, size_t col) const override {
        auto indexes = ProcessIndexes(col, row);
        return (*this->matrix_)[indexes.first, indexes.second];
    }

    T& operator[](size_t row, size_t col) override {
        auto indexes = ProcessIndexes(col, row);
        return (*this->matrix_)[indexes.first, indexes.second];
    }

private:
    std::pair<size_t, size_t> ProcessIndexes(size_t col, size_t row) const {
        if (col == columns.first) {
            col = columns.second;
        } else if (col == columns.second) {
            col = columns.first;
        }

        if (row == rows.first) {
            row = rows.second;
        } else if (row == rows.second) {
            row = rows.first;
        }

        return {row, col};
    }

    std::pair<size_t, size_t> columns = {0, 0};
    std::pair<size_t, size_t> rows = {0, 0};
};
}  // namespace my_math_lib