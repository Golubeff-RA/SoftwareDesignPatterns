#pragma once

#include "matrix_drawer/imatrix_drawer.h"

template <typename T>
class GrapicalMatrixDrawer : public IMatrixDrawer<T> {
public:
    void DrawMatrix(MatrixPtr<T> matrix, DrawerPtr drawer,
                    SerializerPtr<T> serializer) const override {
        size_t max_len = this->CalcMaxElemLength(matrix, serializer);
        DrawBorder(matrix, drawer, max_len);
        ImVec2 current_pos{1, 1};
        for (size_t i = 0; i < matrix->Rows(); ++i) {
            for (size_t j = 0; j < matrix->Columns(); ++j) {
                drawer->DrawText(
                    current_pos,
                    serializer->ProcessElem(matrix, i, j, max_len).c_str());
                current_pos.x += 11 * max_len;
            }
            current_pos.x = 1;
            current_pos.y += 24;
        }
    }

protected:
    void DrawBorder(MatrixPtr<T> matrix, DrawerPtr drawer,
                    size_t max_len) const {
        float border_width = matrix->Columns() * 11 * max_len;
        float border_height = matrix->Rows() * 24;
        drawer->DrawLine(ImVec2(0, 0), ImVec2(border_width, 0));
        drawer->DrawLine(ImVec2(0, 0), ImVec2(0, border_height));
        drawer->DrawLine(ImVec2(border_width, 0),
                         ImVec2(border_width, border_height));
        drawer->DrawLine(ImVec2(0, border_height),
                         ImVec2(border_width, border_height));
    }
};
