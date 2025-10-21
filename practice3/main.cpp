#include <imgui.h>

#include <iostream>

#include "app/app.h"
#include "drawer/default_drawer.h"
#include "drawer/idrawer.h"
#include "drawer/lazy_drawer.h"
#include "initializers/matrix_initializer.h"
#include "matrix/matrix.h"
#include "matrix/sparse_matrix.h"
#include "matrix_drawer/dense_matrix_drawer.h"
#include "matrix_drawer/sparse_matrix_drawer.h"
#include "pretty_printers/printer.h"

using namespace my_math_lib;

void Practice3Render() {
    static MatrixPtr<int> dense_matrix = nullptr;
    static MatrixPtr<int> sparse_matrix = nullptr;

    static DrawerPtr drawer = DrawerPtr(new DefaultDrawer());
    static DenseMatrixDrawer<int> dense_m_drawer;
    static SparseMatrixDrawer<int> sparse_m_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    ImGui::Begin("User Interface for LAB2");

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button("  Generate\ndense matrix", ImVec2(120, 36))) {
        dense_matrix = MatrixPtr<int>(new Matrix<int>(10, 10));
        MatrixInitializer::FillMatrix<int>(dense_matrix, 30, 300);
    }

    ImGui::SameLine();
    if (ImGui::Button("  Generate\nsparce matrix", ImVec2(120, 36))) {
        sparse_matrix = MatrixPtr<int>(new Matrix<int>(10, 10));
        MatrixInitializer::FillMatrix<int>(sparse_matrix, 30, 300);
    }

    ImGui::SameLine();
    if (ImGui::Button("  Border\n optinon", ImVec2(120, 36))) {
        if (std::dynamic_pointer_cast<LazyDrawer>(drawer) == nullptr) {
            drawer = DrawerPtr(new LazyDrawer());
        } else {
            drawer = DrawerPtr(new DefaultDrawer());
        }   
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if (dense_matrix != nullptr) {
        dense_m_drawer.DrawMatrix(dense_matrix, draw_list,
                                  ImVec2(window_pos.x + 12, window_pos.y + 84), drawer);
    }

    if (sparse_matrix != nullptr) {
        sparse_m_drawer.DrawMatrix(sparse_matrix, draw_list,
                                   ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84),
                                   drawer);
    }
    ImGui::End();
}

int main() {
    App app(1280, 720, "Software Design Patterns Labs");
    app.SetRenderCallback(Practice3Render);
    app.Run();
    return 0;
}