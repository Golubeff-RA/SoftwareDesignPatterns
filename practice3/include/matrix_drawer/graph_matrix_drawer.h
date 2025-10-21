#pragma once

#include "matrix_drawer/imatrix_drawer.h"

template <typename T>
class GrapicalMatrixDrawer : public IMatrixDrawer<T> {
public:
    void DrawMatrix(MatrixPtr<T> matrix, DrawerPtr drawer,
                    SerializerPtr<T> serializer) const override {
        size_t max_len = this->CalcMaxElemLength(matrix, serializer);
        DrawBorder(matrix, drawer->GetPos(), drawer, max_len);
        ImVec2 current_pos{drawer->GetPos().x + 1, drawer->GetPos().y + 1};
        for (size_t i = 0; i < matrix.get()->Rows(); ++i) {
            for (size_t j = 0; j < matrix.get()->Columns(); ++j) {
                drawer.get()->DrawText(current_pos,
                                       serializer.get()->ProcessElem(matrix, i, j, max_len).c_str());
                current_pos.x += 11 * max_len;
            }
            current_pos.x = drawer->GetPos().x + 1;
            current_pos.y += 24;
        }
    }

protected:
    void DrawBorder(MatrixPtr<T> matrix, ImVec2 pos, DrawerPtr drawer, size_t max_len) const {
        float border_width = matrix.get()->Columns() * 11 * max_len + 10;
        float border_height = matrix.get()->Rows() * 24;
        drawer.get()->DrawLine(pos, ImVec2(pos.x + border_width, pos.y));
        drawer.get()->DrawLine(pos, ImVec2(pos.x, pos.y + border_height));
        drawer.get()->DrawLine(ImVec2(pos.x + border_width, pos.y),
                               ImVec2(pos.x + border_width, pos.y + border_height));
        drawer.get()->DrawLine(ImVec2(pos.x, pos.y + border_height),
                               ImVec2(pos.x + border_width, pos.y + border_height));
    }
};
