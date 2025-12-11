#pragma once
#include <concepts>

#include "complex_num.h"

template <class T>
concept CanCompare =
    requires(const ComplexNumber& left, const ComplexNumber& right) {
        { T::operator()(left, right) } -> std::same_as<bool>;
    };

class FirstStrategy {
public:
    static bool operator()(const ComplexNumber& left,
                           const ComplexNumber& right) {
        return left.real < right.real;
    }
};

class SecondStrategy {
public:
    static bool operator()(const ComplexNumber& left,
                           const ComplexNumber& right) {
        return left.im < right.im;
    }
};

template <CanCompare Strategy>
class InverseDecorator {
public:
    static bool operator()(const ComplexNumber& left,
                           const ComplexNumber& right) {
        return !Strategy::operator()(left, right);
    }
};
