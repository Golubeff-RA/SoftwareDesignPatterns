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