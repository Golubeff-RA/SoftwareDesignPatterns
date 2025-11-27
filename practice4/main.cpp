#include <initializers/matrix_initializer.h>
#include <matrix/matrix.h>
#include <matrix/sparse_matrix.h>
#include <pretty_printers/printer.h>
#include <swap_decorator.h>

#include <iostream>

#include "transpose_decorator.h"

using namespace my_math_lib;

int main() {
    MatrixPtr<int> matrix = MatrixPtr<int>(new Matrix<int>(2, 6));
    MatrixInitializer::FillMatrix<int>(matrix, 9, 300);
    MatrixPtr<int> decorator_ptr =
        MatrixPtr<int>(new TransposeDecorator<int>(matrix));
    Printer::PrintMatrix<int>(decorator_ptr, std::cout);
    Printer::PrintMatrix<int>(matrix, std::cout);

    return 0;
}