#pragma once
#include "matrix_drawer/imatrix_drawer.h"

template <typename T>
class ConsoleMatrixDrawer : IMatrixDrawer<T> {
public:
    void DrawMatrix(MatrixPtr<T> matrix, DrawerPtr drawer,
                    SerializerPtr<T> serializer) const override {
        size_t max_len = this->CalcMaxElemLength(matrix, serializer);
        DrawBorderConsole(matrix, drawer, max_len);
        for (size_t i = 0; i < matrix.get()->Rows(); ++i) {
            drawer.get()->DrawBorder('|');
            for (size_t j = 0; j < matrix.get()->Columns(); ++j) {
                drawer.get()->DrawText(serializer.get()->ProcessElem(matrix, i, j, max_len + 1).c_str());
            }
            drawer.get()->DrawBorder('|');
            drawer.get()->DrawText("\n");
        }
        DrawBorderConsole(matrix, drawer, max_len);
    }

private:
    void DrawBorderConsole(MatrixPtr<T> matrix, DrawerPtr drawer, size_t max_len) const {
        drawer.get()->DrawBorder('+');
        for (size_t i = 0; i < matrix.get()->Columns() * (max_len + 1); ++i) {
            drawer.get()->DrawBorder('-');
        }
        drawer.get()->DrawBorder('+');
        drawer.get()->DrawText("\n");
    }
};