#pragma once
#include <matrix/imatrix.h>

namespace my_math_lib {
template <typename T>
class ISerializer {
public:
    virtual std::string ProcessElem(MatrixPtr<T> matrix, size_t row, size_t col, size_t min_str_len) const = 0;
    virtual ~ISerializer() = default;
};

template <typename T>
using SerializerPtr = std::shared_ptr<ISerializer<T>>;

template <typename T>
class DenseSerializer : public ISerializer<T> {
public:
    std::string ProcessElem(MatrixPtr<T> matrix, size_t row, size_t col, size_t min_str_len) const override {
        return BasicProcessing<T>(matrix, row, col, min_str_len);
    }
};

template <typename T>
class SparseSerializer : public ISerializer<T> {
public:
    std::string ProcessElem(MatrixPtr<T> matrix, size_t row, size_t col, size_t min_str_len) const override {
        if (matrix.get()->operator()(row, col) == T{}){
            return std::string(min_str_len, ' ');
        }
        return BasicProcessing<T>(matrix, row, col, min_str_len);
    }
};

template <typename T>
std::string BasicProcessing(MatrixPtr<T> matrix, size_t row, size_t col, size_t min_size = 6) {
    std::string val = std::to_string(matrix.get()->operator()(row, col));
    if (val.length() < min_size) {
        val = std::string(min_size - val.length(), ' ') + val;
    }
    return val;
}


}  // namespace my_math_lib