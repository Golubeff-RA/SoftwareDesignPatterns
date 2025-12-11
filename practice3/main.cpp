#include <imgui.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "acommand.h"
#include "app/app.h"
#include "command_manager.h"
#include "drawer/default_drawer.h"
#include "drawer/idrawer.h"
#include "drawer/lazy_drawer.h"
#include "initializers/matrix_initializer.h"
#include "matrix/imatrix.h"
#include "matrix/matrix.h"
#include "matrix/sparse_matrix.h"
#include "matrix_drawer/console_matrix_drawer.h"
#include "matrix_drawer/graph_matrix_drawer.h"
#include "matrix_group.h"
#include "random_generator/random_generator.h"
#include "serializers/serializers.h"
#include "swap_decorator.h"

using namespace my_math_lib;
using std::pair;

pair<pair<size_t, size_t>, pair<size_t, size_t>> RandomSwap(size_t rows,
                                                            size_t columns) {
    pair<size_t, size_t> cols_pair{0, 0};
    pair<size_t, size_t> rows_pair{0, 0};

    RandomGenerator<size_t> gena;
    if (columns >= 2) {
        cols_pair.first = gena.Generate(0, columns - 1);
        do {
            cols_pair.second = gena.Generate(0, columns - 1);
        } while (cols_pair.first == cols_pair.second);
    }

    if (rows >= 2) {
        rows_pair.first = gena.Generate(0, rows - 1);
        do {
            rows_pair.second = gena.Generate(0, rows - 1);
        } while (rows_pair.first == rows_pair.second);
    }

    return {rows_pair, cols_pair};
}

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
    // static bool swap_option = true;

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
        if (dense_matrix->Columns() > 0 && dense_matrix->Rows() > 2) {
            auto indexes =
                RandomSwap(dense_matrix->Rows(), dense_matrix->Columns());
            std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)
                ->SwapRows(indexes.first.first, indexes.first.second);
            std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)
                ->SwapColumns(indexes.second.first, indexes.second.second);
        }

        if (sparse_matrix->Columns() > 0 && sparse_matrix->Rows() > 2) {
            auto indexes =
                RandomSwap(sparse_matrix->Rows(), sparse_matrix->Columns());
            std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                ->SwapRows(indexes.first.first, indexes.first.second);
            std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                ->SwapColumns(indexes.second.first, indexes.second.second);
        }

        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button(" Undecorate\n ", ImVec2(120, 36))) {
        std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)->Repare();
        std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)->Repare();
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

template <typename T, class Matr>
MatrixPtr<T> GetGroupOfMatr() {
    MatrixPtr<T> group_1 = std::make_shared<HorizontalGroup<T>>();
    std::dynamic_pointer_cast<HorizontalGroup<T>>(group_1)->AddMatrix(
        std::make_shared<Matr>(5, 5));
    std::dynamic_pointer_cast<HorizontalGroup<T>>(group_1)->AddMatrix(
        std::make_shared<Matr>(3, 3));
    std::dynamic_pointer_cast<HorizontalGroup<T>>(group_1)->AddMatrix(
        std::make_shared<Matr>(7, 2));
    std::dynamic_pointer_cast<HorizontalGroup<T>>(group_1)->AddMatrix(
        std::make_shared<Matr>(8, 1));

    MatrixPtr<T> group_2 = std::make_shared<HorizontalGroup<T>>();
    std::dynamic_pointer_cast<HorizontalGroup<T>>(group_2)->AddMatrix(
        std::make_shared<Matr>(5, 4));
    std::dynamic_pointer_cast<HorizontalGroup<T>>(group_2)->AddMatrix(
        std::make_shared<Matr>(1, 3));

    MatrixPtr<T> third = std::make_shared<Matr>(8, 2);

    MatrixPtr<T> answer = std::make_shared<VerticalGroup<T>>();
    std::dynamic_pointer_cast<VerticalGroup<T>>(answer)->AddMatrix(group_1);
    std::dynamic_pointer_cast<VerticalGroup<T>>(answer)->AddMatrix(group_2);
    std::dynamic_pointer_cast<VerticalGroup<T>>(answer)->AddMatrix(third);

    return answer;
}

template <typename T>
void Practice5Render() {
    static bool border_option = false;

    static SerializerPtr<T> serializer_for_dense =
        std::make_shared<DenseSerializer<T>>();
    static SerializerPtr<T> serializer_for_sparse =
        std::make_shared<SparseSerializer<T>>();

    static MatrixPtr<T> dense_matrix =
        std::make_shared<SwapDecorator<T>>(std::make_shared<Matrix<T>>(0, 0));
    static MatrixPtr<T> sparse_matrix = std::make_shared<SwapDecorator<T>>(
        std::make_shared<SparseMatrix<T>>(0, 0));

    static DrawerPtr drawer_for_dense = nullptr;
    static DrawerPtr drawer_for_sparse = nullptr;
    static GrapicalMatrixDrawer<T> graph_drawer;
    static ConsoleMatrixDrawer<T> console_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    size_t changes_count = 0;

    ImGui::Begin("User interface for LAB4");

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button("  Generate\ndense matrix", ImVec2(120, 36))) {
        MatrixPtr<T> matrix = GetGroupOfMatr<T, Matrix<T>>();
        MatrixInitializer::FillMatrix<T>(
            matrix, matrix->Rows() * matrix->Columns(), 9000);
        // dense_matrix = std::make_shared<SwapDecorator<T>>(matrix);
        dense_matrix = matrix;
        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button("  Generate\nsparce matrix", ImVec2(120, 36))) {
        MatrixPtr<T> matrix = GetGroupOfMatr<T, SparseMatrix<T>>();
        MatrixInitializer::FillMatrix<T>(
            matrix, matrix->Rows() * matrix->Columns(), 9000);
        // sparse_matrix = std::make_shared<SwapDecorator<T>>(matrix);
        sparse_matrix = matrix;
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
        if (std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix) ==
            nullptr) {
            dense_matrix = std::make_shared<SwapDecorator<T>>(dense_matrix);
        }

        if (std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix) ==
            nullptr) {
            sparse_matrix = std::make_shared<SwapDecorator<T>>(sparse_matrix);
        }

        if (dense_matrix->Columns() > 0 && dense_matrix->Rows() > 2) {
            auto indexes =
                RandomSwap(dense_matrix->Rows(), dense_matrix->Columns());
            std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)
                ->SwapRows(indexes.first.first, indexes.first.second);
            std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)
                ->SwapColumns(indexes.second.first, indexes.second.second);
        }

        if (sparse_matrix->Columns() > 0 && sparse_matrix->Rows() > 2) {
            auto indexes =
                RandomSwap(sparse_matrix->Rows(), sparse_matrix->Columns());
            std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                ->SwapRows(indexes.first.first, indexes.first.second);
            std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                ->SwapColumns(indexes.second.first, indexes.second.second);
        }

        ++changes_count;
    }

    ImGui::SameLine();
    if (ImGui::Button(" Undecorate\n ", ImVec2(120, 36))) {
        if (std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix) !=
            nullptr) {
            dense_matrix =
                std::dynamic_pointer_cast<SwapDecorator<T>>(dense_matrix)
                    ->UnDecorate();
            sparse_matrix =
                std::dynamic_pointer_cast<SwapDecorator<T>>(sparse_matrix)
                    ->UnDecorate();
            ++changes_count;
        }
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

struct PackForModify {
    size_t row;
    size_t col;
    double value;
};

PackForModify ForRandomModify(MatrixPtr<double> matrix) {
    PackForModify answer;
    auto idxs = RandomSwap(matrix->Rows(), matrix->Columns());
    answer.row = idxs.first.first;
    answer.col = idxs.second.first;
    RandomGenerator<double> gena;
    answer.value = gena.Generate(0, 99);
    return answer;
}

void Practice6Render() {
    static bool init_flag = false;
    static bool border_option = false;
    static SerializerPtr<double> serializer =
        std::make_shared<SparseSerializer<double>>();

    static MatrixPtr<double> matrix = std::make_shared<Matrix<double>>(20, 10);

    static DrawerPtr drawer = nullptr;
    static GrapicalMatrixDrawer<double> graph_drawer;
    static ConsoleMatrixDrawer<double> console_drawer;

    static ImVec2 window_pos;
    static ImVec2 window_size;

    size_t changes_count = 0;

    ImGui::Begin("User interface for LAB5");

    if (!init_flag) {
        InitAppCommand init_cmd(matrix);
        init_cmd.Execute();
        init_flag = true;
    }

    window_pos = ImGui::GetWindowPos();
    window_size = ImGui::GetWindowSize();
    if (ImGui::Button(" Modify\n matrix", ImVec2(120, 36))) {
        ++changes_count;
        PackForModify pack(ForRandomModify(matrix));
        SetMatrixValueCommand set1(matrix, pack.row, pack.col, pack.value);
        pack = ForRandomModify(matrix);
        SetMatrixValueCommand set2(matrix, pack.row, pack.col, pack.value);
        pack = ForRandomModify(matrix);
        SetMatrixValueCommand set3(matrix, pack.row, pack.col, pack.value);
        pack = ForRandomModify(matrix);
        SetMatrixValueCommand set4(matrix, pack.row, pack.col, pack.value);
        set1.Execute();
        set2.Execute();
        set3.Execute();
        set4.Execute();
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGui::SameLine();
    if (ImGui::Button("Undo", ImVec2(120, 36))) {
        ++changes_count;
        CommandManager::Instance()->UndoLastCmd();
    }

    ImGui::SameLine();
    if (ImGui::Button(" Border\n Option", ImVec2(120, 36))) {
        border_option = !border_option;
        ++changes_count;
    }

    if (border_option) {
        drawer = DrawerPtr(
            new DefaultDrawer(draw_list, std::cout,
                              ImVec2(window_pos.x + 12, window_pos.y + 84)));
    } else {
        drawer = DrawerPtr(
            new LazyDrawer(draw_list, std::cout,
                           ImVec2(window_pos.x + 12, window_pos.y + 84)));
    }

    graph_drawer.DrawMatrix(matrix, drawer, serializer);

    if (changes_count != 0) {
        std::system("clear");
        console_drawer.DrawMatrix(matrix, drawer, serializer);
    }
    ImGui::End();
}

int main() {
    App app(1280, 720, "Software Design Patterns Labs");
    app.SetRenderCallback(Practice6Render);
    app.Run();
    return 0;
}