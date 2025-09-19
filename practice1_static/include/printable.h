#pragma once
#include <printer.h>

#include <tuple>

template <Printable ToPrint>
class IPrintable {
public:
    IPrintable(ToPrint data) : data_(data) {}

    template <class Printer>
    void Print(Printer) const {
        Printer::Print(data_);
    }

private:
    ToPrint data_;
};

template <typename... Args>
class Text {
public:
    Text(Args&&... args) : data_(std::forward<Args>(args)...) {}
    template <class Printer>
    void Print() const {
        RecursivePrint<Printer, 0>();
    }

private:
    template <class Printer, size_t Idx>
    void RecursivePrint() const {
        if constexpr (Idx >= std::tuple_size_v<decltype(data_)>) {
            return;
        } else {
            std::get<Idx>(data_).Print(Printer());
            return RecursivePrint<Printer, Idx + 1>();
        }
    }

    std::tuple<Args...> data_;
};
