#pragma once
#include <memory>
namespace my_math_lib {
template <typename T>
class IMatrix {
public:
    virtual ~IMatrix() = default;
    virtual size_t Rows() const = 0;
    virtual size_t Columns() const = 0;
    virtual T operator()(size_t row, size_t col) const = 0;
    virtual T& operator()(size_t row, size_t col) = 0;
};

template <typename T>
using MatrixPtr = std::shared_ptr<IMatrix<T>>;
}  // namespace my_math_lib