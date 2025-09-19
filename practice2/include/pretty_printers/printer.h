#pragma once
#include <statistica/statistica.h>

#include <concepts>
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
                out << std::setw(8) << matrix->operator()(i, j) << ' ';
            }
            out << std::endl;
        }
    }

    template <Printable T>
    static void PrintStatistics(const StatisticOfMatrix<T>& statistics, std::ostream& out) {
        out << "Статистика по матрице:\n";
        out << "Сумма значений           : " << statistics.Sum() << std::endl;
        out << "Среднее значение         : " << statistics.Avg() << std::endl;
        out << "Макс. значение           : " << statistics.Max() << std::endl;
        out << "Число ненулевых элементов: " << statistics.NonZeroCnt() << std::endl;
    }
};

}  // namespace my_math_lib