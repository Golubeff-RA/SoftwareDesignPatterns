#pragma once
#include <matrix_drawer/amatrix_drawer.h>

template <typename T>
class DenseMatrixDrawer : public AMatrixDrawer<T> {
protected:
    std::string ProcessElement(MatrixPtr<T> matrix, size_t i, size_t j) const override {
        return BasicProcessing(matrix, i, j);
    }
};