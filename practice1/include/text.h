#pragma once

#include <iprintable.h>

#include <list>

class Text : public IPrintable {
public:
    Text(const std::list<PrintablePtr>& args) : data_(args) {}

    void Print(PrinterPtr printer) const override {
        for (const auto& word : data_) {
            word->Print(printer);
        }
    }

private:
    std::list<PrintablePtr> data_;
};

template<typename ... Args>
class Text2 : public IPrintable {
public:
    Text2(Args&& ... args) {
        (data_.push_back(std::forward<Args>(args)), ...);
    }

    void Print(PrinterPtr printer) const override {
        for (const auto& word : data_) {
            word->Print(printer);
        }
    }

private:
    std::list<PrintablePtr> data_;
};