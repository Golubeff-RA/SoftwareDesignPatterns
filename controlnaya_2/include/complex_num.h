#pragma once
#include <iomanip>
#include <ostream>

struct ComplexNumber {
    double real;
    double im;
};

inline std::ostream& operator<<(std::ostream& stream,
                                const ComplexNumber& num) {
    return stream << "r: " << std::setw(5) << num.real << " i: " << std::setw(5)
                  << num.im;
}