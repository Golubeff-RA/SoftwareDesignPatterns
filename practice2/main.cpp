#include <iostream>

#include "initializers/matrix_initializer.h"
#include "matrix/matrix.h"
#include "matrix/sparse_matrix.h"
#include "pretty_printers/printer.h"
#include "statistica/statistica.h"

using namespace my_math_lib;

int main() {
    MatrixPtr<double> matrix_classic =
        MatrixPtr<double>(new Matrix<double>(10, 10));
    MatrixPtr<double> matrix_sparse =
        MatrixPtr<double>(new SparseMatrix<double>(5, 10));

    MatrixInitializer::FillMatrix(matrix_classic, 33, 30.0);
    MatrixInitializer::FillMatrix(matrix_sparse, 20, 100.0);

    Printer::PrintMatrix(matrix_classic, std::cout);
    Printer::PrintStatistics(
        StatisticCalculator<double>::GetStatistics(matrix_classic), std::cout);
    std::cout << std::endl;
    Printer::PrintMatrix(matrix_sparse, std::cout);
    Printer::PrintStatistics(
        StatisticCalculator<double>::GetStatistics(matrix_sparse), std::cout);
    return 0;
}