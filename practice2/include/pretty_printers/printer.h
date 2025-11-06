#pragma once
#include <statistica/statistica.h>

#include <concepts>
#include <iomanip>
namespace my_math_lib {

template <typename T>
concept Printable = requires(std::ostream& os, T value) {
    { os << value } -> std::same_as<std::ostream&>;
};

class Printer {
public:
    template <Printable T>
    static void PrintMatrix(const MatrixPtr<T> matrix, std::ostream& out) {
        out << "Матрица хранит тип: " << typeid(T).name() << std::endl;
        out << "Размер: " << matrix->Rows() << 'x' << matrix->Columns() << std::endl;
        for (size_t i = 0; i < matrix->Rows(); ++i) {
            for (size_t j = 0; j < matrix.get()->Columns(); ++j) {
                out << std::setw(8) << (*matrix)[i, j] << ' ';
            }
            out << std::endl;
        }
    }

    template <Printable T>
    static void PrintStatistics(const Metrics<T>& metrics, std::ostream& out) {
        out << "Статистика по матрице:\n";
        out << "Сумма значений           : " << metrics.sum << std::endl;
        out << "Среднее значение         : " << metrics.avg << std::endl;
        out << "Макс. значение           : " << metrics.max << std::endl;
        out << "Число ненулевых элементов: " << metrics.non_zero_cnt << std::endl;
    }
};

}  // namespace my_math_lib