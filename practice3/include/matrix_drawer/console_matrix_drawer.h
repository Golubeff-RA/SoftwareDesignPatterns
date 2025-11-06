#pragma once
#include "matrix_drawer/imatrix_drawer.h"

template <typename T>
class ConsoleMatrixDrawer : IMatrixDrawer<T> {
public:
    void DrawMatrix(MatrixPtr<T> matrix, DrawerPtr drawer,
                    SerializerPtr<T> serializer) const override {
        size_t max_len = this->CalcMaxElemLength(matrix, serializer);
        DrawBorderConsole(matrix, drawer, max_len);
        for (size_t i = 0; i < matrix->Rows(); ++i) {
            drawer.get()->DrawLine('|');
            for (size_t j = 0; j < matrix->Columns(); ++j) {
                drawer->DrawText(
                    serializer->ProcessElem(matrix, i, j, max_len + 1).c_str());
            }
            drawer->DrawLine('|');
            drawer->DrawText("\n");
        }
        DrawBorderConsole(matrix, drawer, max_len);
    }

private:
    void DrawBorderConsole(MatrixPtr<T> matrix, DrawerPtr drawer,
                           size_t max_len) const {
        if (matrix->Columns() == 0) {
            return;
        }
        drawer->DrawLine('+');
        for (size_t i = 0; i < matrix->Columns() * (max_len + 1); ++i) {
            drawer->DrawLine('-');
        }
        drawer->DrawLine('+');
        drawer->DrawText("\n");
    }
};