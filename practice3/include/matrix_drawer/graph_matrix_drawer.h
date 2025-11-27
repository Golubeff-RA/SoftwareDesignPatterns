#pragma once

#include <memory>

#include "drawer/default_drawer.h"
#include "imgui.h"
#include "matrix_drawer/imatrix_drawer.h"
#include "matrix_group.h"

template <typename T>
class GrapicalMatrixDrawer : public IMatrixDrawer<T> {
public:
    void DrawMatrix(MatrixPtr<T> matrix, DrawerPtr drawer,
                    SerializerPtr<T> serializer) const override {
        size_t max_len = this->CalcMaxElemLength(matrix, serializer);
        DrawBorder({matrix->Rows(), matrix->Columns()}, drawer, max_len);
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

        if (std::dynamic_pointer_cast<HorizontalGroup<T>>(matrix) != nullptr) {
            auto sizes = std::dynamic_pointer_cast<HorizontalGroup<T>>(matrix)
                             ->GetMatricesSizes();
            float temp_x = 0;
            for (auto size : sizes) {
                ImVec2 pos{drawer->GetStartPos().x + temp_x,
                           drawer->GetStartPos().y};
                DrawerPtr drawer_new = std::make_shared<DefaultDrawer>(
                    drawer->GetDrawList(), drawer->GetOut(), pos);
                DrawBorder({size.first, size.second}, drawer_new, max_len);
                temp_x += size.second * 11 * max_len;
            }
        } else if (std::dynamic_pointer_cast<VerticalGroup<T>>(matrix) !=
                   nullptr) {
            auto sizes = std::dynamic_pointer_cast<VerticalGroup<T>>(matrix)
                             ->GetMatricesSizes();
            float temp_y = 0;
            for (auto size : sizes) {
                ImVec2 pos{drawer->GetStartPos().x,
                           drawer->GetStartPos().y + temp_y};
                DrawerPtr drawer_new = std::make_shared<DefaultDrawer>(
                    drawer->GetDrawList(), drawer->GetOut(), pos);
                DrawBorder({size.second, size.first}, drawer_new, max_len);
                temp_y += size.second * 24;
            }
        }
    }

protected:
    void DrawBorder(std::pair<size_t, size_t> sizes, DrawerPtr drawer,
                    size_t max_len) const {
        float border_width = sizes.second * 11 * max_len;
        float border_height = sizes.first * 24;
        drawer->DrawLine(ImVec2(0, 0), ImVec2(border_width, 0));
        drawer->DrawLine(ImVec2(0, 0), ImVec2(0, border_height));
        drawer->DrawLine(ImVec2(border_width, 0),
                         ImVec2(border_width, border_height));
        drawer->DrawLine(ImVec2(0, border_height),
                         ImVec2(border_width, border_height));
    }
};
