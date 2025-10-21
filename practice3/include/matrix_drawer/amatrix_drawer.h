#pragma once

#include "matrix_drawer/imatrix_drawer.h"

template <typename T>
class AMatrixDrawer : public IMatrixDrawer<T> {
public:
    void DrawMatrix(MatrixPtr<T> matrix, ImDrawList* draw_list, ImVec2 pos,
                    DrawerPtr drawer) const override {
        DrawBorder(matrix, draw_list, pos, drawer);
        ImVec2 current_pos{pos.x + 1, pos.y + 1};
        for (size_t i = 0; i < matrix.get()->Rows(); ++i) {
            for (size_t j = 0; j < matrix.get()->Columns(); ++j) {
                drawer.get()->DrawText(draw_list, current_pos,
                                       ProcessElement(matrix, i, j).c_str());
                current_pos.x += 48;
            }
            current_pos.x = pos.x + 1;
            current_pos.y += 24;
        }
    }

protected:
    virtual std::string ProcessElement(MatrixPtr<T> matrix, size_t i, size_t j) const = 0;
    void DrawBorder(MatrixPtr<T> matrix, ImDrawList* draw_list, ImVec2 pos,
                    DrawerPtr drawer) const override {
        float border_width = matrix.get()->Columns() * 48 + 10;
        float border_height = matrix.get()->Rows() * 24;
        drawer.get()->DrawLine(draw_list, pos, ImVec2(pos.x + border_width, pos.y));
        drawer.get()->DrawLine(draw_list, pos, ImVec2(pos.x, pos.y + border_height));
        drawer.get()->DrawLine(draw_list, ImVec2(pos.x + border_width, pos.y),
                               ImVec2(pos.x + border_width, pos.y + border_height));
        drawer.get()->DrawLine(draw_list, ImVec2(pos.x, pos.y + border_height),
                               ImVec2(pos.x + border_width, pos.y + border_height));
    }
};

template <typename T>
std::string BasicProcessing(MatrixPtr<T> matrix, size_t i, size_t j, size_t min_size = 6) {
    std::string val = std::to_string(matrix.get()->operator()(i, j));
    if (val.length() < min_size) {
        val = std::string(min_size - val.length(), ' ') + val;
    }
    return val;
}