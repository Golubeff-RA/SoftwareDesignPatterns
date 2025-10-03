#pragma once
#include <matrix/imatrix.h>

namespace my_math_lib {
template <typename T>
class StatisticOfMatrix {
public:
    StatisticOfMatrix(MatrixPtr<T> matrix) : matrix_(matrix) {}

    T Sum() const {
        UpdateStatistics();
        return metrics_.sum;
    }

    T Avg() const {
        UpdateStatistics();
        return metrics_.avg;
    }

    T Max() const {
        UpdateStatistics();
        return metrics_.max;
    }

    size_t NonZeroCnt() const {
        UpdateStatistics();
        return metrics_.non_zero_cnt;
    }

private:
    struct Metrics {
        T sum = T{};
        T avg = T{};
        T max = T{};
        size_t non_zero_cnt = 0;
    };

    mutable Metrics metrics_;
    MatrixPtr<T> matrix_;

    void UpdateStatistics() const {
        metrics_ = Metrics{};
        for (size_t i = 0; i < matrix_->Rows(); ++i) {
            for (size_t j = 0; j < matrix_->Columns(); ++j) {
                metrics_.sum += matrix_->operator()(i, j);
                metrics_.max = std::max(metrics_.max, matrix_->operator()(i, j));
                if (matrix_->operator()(i, j) != T{}) {
                    ++metrics_.non_zero_cnt;
                }
            }
        }

        metrics_.avg = metrics_.sum / (matrix_->Rows() * matrix_->Columns());
    }
};
}  // namespace my_math_lib