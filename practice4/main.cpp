#include <matrix/matrix.h>
#include <matrix/sparse_matrix.h>
#include <swap_decorator.h>
#include <pretty_printers/printer.h>
#include <initializers/matrix_initializer.h>
#include <iostream>

using namespace my_math_lib;

int main() {
    MatrixPtr<int> matrix = MatrixPtr<int>(new Matrix<int>(10, 10));
    MatrixInitializer::FillMatrix<int>(matrix, 20, 300);
    MatrixPtr<int> decorator_ptr = MatrixPtr<int>(new SwapDecorator<int>(matrix));
    Printer::PrintMatrix<int>(decorator_ptr, std::cout);
    std::dynamic_pointer_cast<SwapDecorator<int>>(decorator_ptr)->RandomSwap();
    Printer::PrintMatrix<int>(decorator_ptr, std::cout);
    std::dynamic_pointer_cast<SwapDecorator<int>>(decorator_ptr)->Repare();
    Printer::PrintMatrix<int>(decorator_ptr, std::cout);
    return 0;
}