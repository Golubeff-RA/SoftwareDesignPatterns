#pragma once
#include "drawer/idrawer.h"
#include "matrix/imatrix.h"

using namespace my_math_lib;

template <typename T>
class IMatrixDrawer {
public:
    virtual void DrawMatrix(MatrixPtr<T> matrix, ImDrawList* draw_list, ImVec2 pos, DrawerPtr drawer) const = 0;
protected:
    virtual void DrawBorder(MatrixPtr<T> matrix, ImDrawList* draw_list, ImVec2 pos, DrawerPtr drawer) const = 0;
};

