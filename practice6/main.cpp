#include <iostream>
#include <memory>

#include "acommand.h"
#include "command_manager.h"
#include "initializers/matrix_initializer.h"
#include "matrix/imatrix.h"
#include "matrix/matrix.h"
#include "pretty_printers/printer.h"
int main() {
    MatrixPtr<double> matrix = MatrixPtr<double>(new Matrix<double>(5, 5));
    MatrixInitializer::FillMatrix<double>(matrix, 24, 40);
    Printer::PrintMatrix(matrix, std::cout);
    InitAppCommand init(matrix);
    init.Execute();
    Printer::PrintMatrix(matrix, std::cout);
    SetMatrixValueCommand set1(matrix, 2, 2, 44);
    set1.Execute();
    Printer::PrintMatrix(matrix, std::cout);
    SetMatrixValueCommand set2(matrix, 1, 1, 33);
    set2.Execute();
    Printer::PrintMatrix(matrix, std::cout);
    CommandManager::Instance()->UndoLastCmd();
    Printer::PrintMatrix(matrix, std::cout);
    CommandManager::Instance()->UndoLastCmd();
    Printer::PrintMatrix(matrix, std::cout);
    CommandManager::Instance()->UndoLastCmd();
    Printer::PrintMatrix(matrix, std::cout);
};