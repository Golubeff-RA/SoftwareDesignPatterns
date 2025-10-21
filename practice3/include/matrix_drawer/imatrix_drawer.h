#pragma once
#include "drawer/idrawer.h"
#include "matrix/imatrix.h"
#include "serializers/serializers.h"

using namespace my_math_lib;

template <typename T>
class IMatrixDrawer {
public:
    virtual void DrawMatrix(MatrixPtr<T> matrix, DrawerPtr drawer, SerializerPtr<T> serializer) const = 0;
protected:
    size_t CalcMaxElemLength(MatrixPtr<T> matrix, SerializerPtr<T> serializer) const {
        size_t max_len = 0;
        for (size_t i = 0; i < matrix.get()->Rows(); ++i) {
            for (size_t j = 0; j < matrix.get()->Columns(); ++j) {
                max_len = std::max(max_len, serializer.get()->ProcessElem(matrix, i, j, 0).size());
            }
        }
        return max_len;
    }
};

