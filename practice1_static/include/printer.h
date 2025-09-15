#pragma once
#include <concepts>
#include <iostream>
#include <string>

template <typename T>
concept Printable = requires(std::ostream& os, T value) {
    { os << value } -> std::same_as<std::ostream&>;
};

class PrinterDefault {
public:
    template <Printable ToPrint>
    static constexpr void Print(ToPrint data) {
        std::cout << data;
    }
};

class PrinterWithScobes {
public:
    template <Printable ToPrint>
    static constexpr void Print(ToPrint data) {
        if constexpr (std::same_as<ToPrint, char>) {
            std::cout << data;
        } else {
            std::cout << '(' << data << ')';
        }
    }
};

class PrinterWithEndl {
public:
    template <Printable ToPrint>
    static constexpr void Print(ToPrint data) {
        if constexpr (std::same_as<ToPrint, char>) {
            std::cout << data;
        } else {
            std::cout << data << std::endl;
        }
    }
};
