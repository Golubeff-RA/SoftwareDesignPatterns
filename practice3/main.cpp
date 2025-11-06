#include <imgui.h>

#include <cstddef>
#include <cstdlib>
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

template <typename T>
void Practice3Render() {
    static bool border_option = true;
    static SerializerPtr<T> serializer_for_dense =
        SerializerPtr<T>(new DenseSerializer<T>());
    static SerializerPtr<T> serializer_for_sparse =
        SerializerPtr<T>(new SparseSerializer<T>());

    static MatrixPtr<T> dense_matrix = MatrixPtr<T>(new Matrix<T>(0, 0));
    static MatrixPtr<T> sparse_matrix = MatrixPtr<T>(new Matrix<T>(0, 0));

    static DrawerPtr drawer_for_dense = nullptr;
    static DrawerPtr drawer_for_sparse = nullptr;
    static GrapicalMatrixDrawer<T> graph_drawer;
    static ConsoleMatrixDrawer<T> console_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    size_t changes_count = 0;

    ImGui::Begin("User interface for LAB2");

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button("  Generate\ndense matrix", ImVec2(120, 36))) {
        dense_matrix = MatrixPtr<T>(new Matrix<T>(15, 4));
        MatrixInitializer::FillMatrix<T>(dense_matrix, 30, 1000);
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button("  Generate\nsparce matrix", ImVec2(120, 36))) {
        sparse_matrix = MatrixPtr<T>(new SparseMatrix<T>(15, 4));
        MatrixInitializer::FillMatrix<T>(sparse_matrix, 40, 1000);
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
            new DefaultDrawer(draw_list, std::cout,
                              ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(new DefaultDrawer(
            draw_list, std::cout,
            ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    } else {
        drawer_for_dense = DrawerPtr(
            new LazyDrawer(draw_list, std::cout,
                           ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(new LazyDrawer(
            draw_list, std::cout,
            ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    }

    graph_drawer.DrawMatrix(dense_matrix, drawer_for_dense,
                            serializer_for_dense);
    graph_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse,
                            serializer_for_sparse);
    if (changes_count != 0) {
        std::system("clear");
        console_drawer.DrawMatrix(dense_matrix, drawer_for_dense,
                                  serializer_for_dense);
        console_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse,
                                  serializer_for_sparse);
    }
    ImGui::End();
}

template <typename T>
void Practice4Render() {
    static bool border_option = false;
    static bool swap_option = true;

    static SerializerPtr<T> serializer_for_dense =
        SerializerPtr<T>(new DenseSerializer<T>());
    static SerializerPtr<T> serializer_for_sparse =
        SerializerPtr<T>(new SparseSerializer<T>());

    static MatrixPtr<T> dense_matrix =
        MatrixPtr<T>(new SwapDecorator<T>(MatrixPtr<T>(new Matrix<T>(0, 0))));
    static MatrixPtr<T> sparse_matrix =
        MatrixPtr<T>(new SwapDecorator<T>(MatrixPtr<T>(new Matrix<T>(0, 0))));

    static DrawerPtr drawer_for_dense = nullptr;
    static DrawerPtr drawer_for_sparse = nullptr;
    static GrapicalMatrixDrawer<T> graph_drawer;
    static ConsoleMatrixDrawer<T> console_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    size_t changes_count = 0;

    ImGui::Begin("User interface for LAB3");

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button("  Generate\ndense matrix", ImVec2(120, 36))) {
        MatrixPtr<T> matrix = MatrixPtr<T>(new Matrix<T>(15, 4));
        MatrixInitializer::FillMatrix<T>(matrix, 30, 1000);
        dense_matrix = MatrixPtr<T>(new SwapDecorator<T>(matrix));
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button("  Generate\nsparce matrix", ImVec2(120, 36))) {
        MatrixPtr<T> matrix = MatrixPtr<T>(new SparseMatrix<T>(15, 4));
        MatrixInitializer::FillMatrix<T>(matrix, 40, 1000);
        sparse_matrix = MatrixPtr<T>(new SwapDecorator<T>(matrix));
        ++changes_count;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGui::SameLine();
    if (ImGui::Button("  Border\n optinon", ImVec2(120, 36))) {
        border_option = !border_option;
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button(" Random\n  Swap ", ImVec2(120, 36))) {
        if (swap_option) {
            std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)
                ->RandomSwap();
            std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                ->RandomSwap();

        } else {
            std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)->Repare();
            std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                ->Repare();
        }
        ++changes_count;
        swap_option = !swap_option;
    }

    if (border_option) {
        drawer_for_dense = DrawerPtr(
            new DefaultDrawer(draw_list, std::cout,
                              ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(new DefaultDrawer(
            draw_list, std::cout,
            ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    } else {
        drawer_for_dense = DrawerPtr(
            new LazyDrawer(draw_list, std::cout,
                           ImVec2(window_pos.x + 12, window_pos.y + 84)));
        drawer_for_sparse = DrawerPtr(new LazyDrawer(
            draw_list, std::cout,
            ImVec2(window_pos.x + 12 + window_size.x / 2, window_pos.y + 84)));
    }

    graph_drawer.DrawMatrix(dense_matrix, drawer_for_dense,
                            serializer_for_dense);
    graph_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse,
                            serializer_for_sparse);

    if (changes_count != 0) {
        std::system("clear");
        console_drawer.DrawMatrix(dense_matrix, drawer_for_dense,
                                  serializer_for_dense);
        console_drawer.DrawMatrix(sparse_matrix, drawer_for_sparse,
                                  serializer_for_sparse);
    }
    ImGui::End();
}

int main() {
    App app(1280, 720, "Software Design Patterns Labs");
    app.SetRenderCallback(Practice4Render<double>);
    app.Run();
    return 0;
}