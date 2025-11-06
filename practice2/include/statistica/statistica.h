#pragma once
#include <matrix/imatrix.h>

namespace my_math_lib {

template <typename T>
struct Metrics {
    T sum = T{};
    T avg = T{};
    T max = T{};
    size_t non_zero_cnt = 0;
};

template <typename T>
class StatisticCalculator {
public:
    static Metrics<T> GetStatistics(const MatrixPtr<T> matrix) {
        Metrics<T> metrics;
        for (size_t i = 0; i < matrix->Rows(); ++i) {
            for (size_t j = 0; j < matrix->Columns(); ++j) {
                metrics.sum += (*matrix)[i, j];
                metrics.max = std::max(metrics.max, (*matrix)[i, j]);
                if ((*matrix)[i, j] != T{}) {
                    ++metrics.non_zero_cnt;
                }
            }
        }

        metrics.avg = metrics.sum / (matrix->Rows() * matrix->Columns());

        return metrics;
    }
};
}  // namespace my_math_lib