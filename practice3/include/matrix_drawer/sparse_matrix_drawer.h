#pragma once
#include <matrix_drawer/amatrix_drawer.h>

template <typename T>
class SparseMatrixDrawer : public AMatrixDrawer<T> {
protected:
    std::string ProcessElement(MatrixPtr<T> matrix, size_t i, size_t j) const override {
        if (matrix.get()->operator()(i, j) == T{}){
            return std::string(6, ' ');
        }
        return BasicProcessing(matrix, i, j, 6);
    }
};