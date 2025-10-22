#pragma once

#include <matrix/imatrix.h>

namespace my_math_lib {
template <typename T>
class IDecorator : public IMatrix<T> {
public:
    IDecorator(MatrixPtr<T> matrix) : matrix_(matrix) {}
    //virtual ~IDecorator() = default;
protected:
    MatrixPtr<T> matrix_;
};
}  // namespace my_math_lib