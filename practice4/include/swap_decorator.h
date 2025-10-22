#pragma once
#include "idecorator.h"
#include "random_generator/random_generator.h"

namespace my_math_lib {
template <typename T>
class SwapDecorator : public IDecorator<T> {
public:
    SwapDecorator(MatrixPtr<T> matrix) : IDecorator<T>(matrix) {}

    void RandomSwap() {
        RandomGenerator<size_t> gena;
        first_id = gena.Generate(0, Columns() - 1);
        do {
            second_id = gena.Generate(0, Columns() - 1);
        } while (second_id == first_id);
    }

    void Repare() {
        first_id = 0;
        second_id = 0;
    }

    size_t Rows() const override { return this->matrix_.get()->Rows(); }

    size_t Columns() const override { return this->matrix_.get()->Columns(); }

    T operator()(size_t row, size_t col) const override {
        col = ProcessCol(col);
        return this->matrix_.get()->operator()(row, col);
    }

    T& operator()(size_t row, size_t col) override {
        col = ProcessCol(col);
        return this->matrix_.get()->operator()(row, col);
    } 
private:
    size_t ProcessCol(size_t col) const {
        if (col == first_id) {
            return second_id;
        }
        
        if (col == second_id) {
            return  first_id;
        }

        return col;
    }
    size_t first_id = 0;
    size_t second_id = 0;
};
}  // namespace my_math_lib