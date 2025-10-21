#pragma once
#include <matrix/imatrix.h>
#include <random_generator/random_generator.h>

namespace my_math_lib {
class MatrixInitializer {
public:
    template <typename T>
    static void FillMatrix(MatrixPtr<T> matrix, size_t not_zero_cnt, T max_value) {
        RandomGenerator<T> gena;
        RandomGenerator<size_t> idx_gena;
        size_t not_zero = 0;
        while (not_zero < not_zero_cnt) {
            size_t i = idx_gena.Generate(0, matrix.get()->Rows() - 1);
            size_t j = idx_gena.Generate(0, matrix.get()->Columns() - 1);
            if (matrix.get()->operator()(i, j) == T{}) {
                ++not_zero;
                matrix->operator()(i, j) = gena.Generate(T{}, max_value);
            }
        }
    }
};

class MatrixZeroer {
public:
    template <typename T>
    static void ZeroMatrix(MatrixPtr<T> matrix) {
        for(size_t i = 0; i < matrix.get()->Rows(); ++i) {
            for (size_t j = 0; j < matrix.get()->Columns(); ++j) {
                if (matrix.get()->operator()(i, j) != T{}) {
                    matrix.get()->operator()(i, j) = T{};
                }
            }
        }
    }
};

}  // namespace my_math_lib