#include <imgui.h>

#include <iostream>

#include "app/app.h"
#include "drawer/default_drawer.h"
#include "drawer/idrawer.h"
#include "drawer/lazy_drawer.h"
#include "initializers/matrix_initializer.h"
#include "matrix/matrix.h"
#include "matrix/sparse_matrix.h"
#include "matrix_drawer/console_matrix_drawer.h"
#include "matrix_drawer/graph_matrix_drawer.h"
#include "serializers/serializers.h"
#include "swap_decorator.h"

using namespace my_math_lib;

void Practice3Render() {
    static bool border_option = true;

    static SerializerPtr serializer_for_dense = SerializerPtr<float>(new DenseSerializer<float>());
    static SerializerPtr serializer_for_sparse =
        SerializerPtr<float>(new SparseSerializer<float>());

    static MatrixPtr<float> dense_matrix = nullptr;
    static MatrixPtr<float> sparse_matrix = nullptr;

    static DrawerPtr drawer_for_dense = nullptr;
    static DrawerPtr drawer_for_sparse = nullptr;
    static GrapicalMatrixDrawer<float> graph_drawer;
    static ConsoleMatrixDrawer<float> console_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    size_t changes_count = 0;

    ImGui::Begin("User interface for LAB2");

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button("  Generate\ndense matrix", ImVec2(120, 36))) {
        dense_matrix = MatrixPtr<float>(new Matrix<float>(15, 4));
        MatrixInitializer::FillMatrix<float>(dense_matrix, 30, 1000);
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button("  Generate\nsparce matrix", ImVec2(120, 36))) {
        sparse_matrix = MatrixPtr<float>(new Matrix<float>(15, 4));
        MatrixInitializer::FillMatrix<float>(sparse_matrix, 40, 1000);
        ++changes_count;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGui::SameLine();
    if (ImGui::Button("  Border\n optinon", ImVec2(120, 36))) {
        border_option = !border_option;
        ++changes_count;
    }

    if (border_option) {
        drawer_for_dense = DrawerPtr(
            new DefaultDrawer(draw_list, std::cout, ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(
            new DefaultDrawer(draw_list, std::cout,
                              ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    } else {
        drawer_for_dense = DrawerPtr(
            new LazyDrawer(draw_list, std::cout, ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(
            new LazyDrawer(draw_list, std::cout,
                           ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    }

    if (dense_matrix != nullptr) {
        graph_drawer.DrawMatrix(dense_matrix, drawer_for_dense, serializer_for_dense);
        if (changes_count != 0) {
            console_drawer.DrawMatrix(dense_matrix, drawer_for_dense, serializer_for_dense);
        }
    }

    if (sparse_matrix != nullptr) {
        graph_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse, serializer_for_sparse);
        if (changes_count != 0) {
            console_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse, serializer_for_sparse);
        }
    }
    ImGui::End();
}

void Practice4Render() {
    static bool border_option = true;
    static bool swap_option = false;

    static SerializerPtr serializer_for_dense = SerializerPtr<float>(new DenseSerializer<float>());
    static SerializerPtr serializer_for_sparse =
        SerializerPtr<float>(new SparseSerializer<float>());

    static MatrixPtr<float> dense_matrix = nullptr;
    static MatrixPtr<float> sparse_matrix = nullptr;

    static DrawerPtr drawer_for_dense = nullptr;
    static DrawerPtr drawer_for_sparse = nullptr;
    static GrapicalMatrixDrawer<float> graph_drawer;
    static ConsoleMatrixDrawer<float> console_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    size_t changes_count = 0;

    ImGui::Begin("User interface for LAB3");

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button("  Generate\ndense matrix", ImVec2(120, 36))) {
        MatrixPtr<float> matrix = MatrixPtr<float>(new Matrix<float>(15, 4));
        MatrixInitializer::FillMatrix<float>(matrix, 30, 1000);
        dense_matrix = MatrixPtr<float>(new SwapDecorator<float>(matrix));
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button("  Generate\nsparce matrix", ImVec2(120, 36))) {
        MatrixPtr<float> matrix = MatrixPtr<float>(new Matrix<float>(15, 4));
        MatrixInitializer::FillMatrix<float>(matrix, 40, 1000);
        sparse_matrix = MatrixPtr<float>(new SwapDecorator<float>(matrix));
        ++changes_count;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGui::SameLine();
    if (ImGui::Button("  Border\n optinon", ImVec2(120, 36))) {
        border_option = !border_option;
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button("  Swap\n columns", ImVec2(120, 36))) {
        if (swap_option) {
            if (dense_matrix) {
                std::dynamic_pointer_cast<SwapDecorator<float>>(dense_matrix)->RandomSwap();
            }
            if (sparse_matrix) {
                std::dynamic_pointer_cast<SwapDecorator<float>>(sparse_matrix)->RandomSwap();
            }
        } else {
            if (dense_matrix) {
                std::dynamic_pointer_cast<SwapDecorator<float>>(dense_matrix)->Repare();
            }
            if (sparse_matrix) {
                std::dynamic_pointer_cast<SwapDecorator<float>>(sparse_matrix)->Repare();
            }
        }
        ++changes_count;
        swap_option = !swap_option;
    }

    if (border_option) {
        drawer_for_dense = DrawerPtr(
            new DefaultDrawer(draw_list, std::cout, ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(
            new DefaultDrawer(draw_list, std::cout,
                              ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    } else {
        drawer_for_dense = DrawerPtr(
            new LazyDrawer(draw_list, std::cout, ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(
            new LazyDrawer(draw_list, std::cout,
                           ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    }

    if (dense_matrix != nullptr) {
        graph_drawer.DrawMatrix(dense_matrix, drawer_for_dense, serializer_for_dense);
        if (changes_count != 0) {
            console_drawer.DrawMatrix(dense_matrix, drawer_for_dense, serializer_for_dense);
        }
    }

    if (sparse_matrix != nullptr) {
        graph_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse, serializer_for_sparse);
        if (changes_count != 0) {
            console_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse, serializer_for_sparse);
        }
    }
    ImGui::End();
}

int main() {
    App app(1280, 720, "Software Design Patterns Labs");
    app.SetRenderCallback(Practice3Render);
    app.Run();
    return 0;
}