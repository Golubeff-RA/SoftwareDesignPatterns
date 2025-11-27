
#include <iostream>
#include <memory>

#include "initializers/matrix_initializer.h"
#include "matrix/imatrix.h"
#include "matrix/matrix.h"
#include "matrix_group.h"
#include "pretty_printers/printer.h"

using namespace my_math_lib;

int main() {
    MatrixPtr<int> first = MatrixPtr<int>(new Matrix<int>(2, 2));
    // MatrixInitializer::FillMatrix(first, 4, 999);
    MatrixPtr<int> second = MatrixPtr<int>(new Matrix<int>(3, 3));
    // MatrixInitializer::FillMatrix(second, 9, 999);
    MatrixPtr<int> third = MatrixPtr<int>(new Matrix<int>(5, 1));
    // MatrixInitializer::FillMatrix(third, 5, 999);
    MatrixPtr<int> fourth = MatrixPtr<int>(new Matrix<int>(1, 1));
    // MatrixInitializer::FillMatrix(fourth, 1, 999);

    MatrixPtr<int> group_ptr = MatrixPtr<int>(new HorizontalGroup<int>());
    std::dynamic_pointer_cast<HorizontalGroup<int>>(group_ptr)->AddMatrix(
        first);
    std::dynamic_pointer_cast<HorizontalGroup<int>>(group_ptr)->AddMatrix(
        second);
    std::dynamic_pointer_cast<HorizontalGroup<int>>(group_ptr)->AddMatrix(
        third);
    std::dynamic_pointer_cast<HorizontalGroup<int>>(group_ptr)->AddMatrix(
        fourth);

    Printer::PrintMatrix(group_ptr, std::cout);

    MatrixPtr<int> first_1 = MatrixPtr<int>(new Matrix<int>(3, 3));
    // MatrixInitializer::FillMatrix(first_1, 9, 999);
    MatrixPtr<int> second_1 = MatrixPtr<int>(new Matrix<int>(3, 3));
    // MatrixInitializer::FillMatrix(second_1, 9, 999);

    MatrixPtr<int> group_ptr_2 = MatrixPtr<int>(new HorizontalGroup<int>());
    std::dynamic_pointer_cast<HorizontalGroup<int>>(group_ptr_2)
        ->AddMatrix(first_1);
    std::dynamic_pointer_cast<HorizontalGroup<int>>(group_ptr_2)
        ->AddMatrix(second_1);
    Printer::PrintMatrix(group_ptr_2, std::cout);

    MatrixPtr<int> first_2 = MatrixPtr<int>(new Matrix<int>(2, 2));
    // MatrixInitializer::FillMatrix(first_2, 4, 999);
    Printer::PrintMatrix(first_2, std::cout);

    MatrixPtr<int> group_ptr_vertical =
        MatrixPtr<int>(new VerticalGroup<int>());
    std::dynamic_pointer_cast<VerticalGroup<int>>(group_ptr_vertical)
        ->AddMatrix(group_ptr);
    std::dynamic_pointer_cast<VerticalGroup<int>>(group_ptr_vertical)
        ->AddMatrix(group_ptr_2);
    std::dynamic_pointer_cast<VerticalGroup<int>>(group_ptr_vertical)
        ->AddMatrix(first_2);
    MatrixInitializer::FillMatrix(
        group_ptr_vertical,
        group_ptr_vertical->Columns() * group_ptr_vertical->Rows(), 999);
    Printer::PrintMatrix(group_ptr_vertical, std::cout);

    return 0;
}