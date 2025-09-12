#pragma once
#include <iprinter.h>

class IPrintable {
public:
    virtual void Print(PrinterPtr printer) const {
    };
};

using PrintablePtr = std::shared_ptr<IPrintable>;

class Word : public IPrintable {
public:
    explicit Word(const std::string& data) : data_(data) {
    }

    explicit Word(std::string&& data) : data_(data) {
    }

    void Print(PrinterPtr printer) const override {
        printer->Print(data_);
    }

private:
    std::string data_;
};

class Sign : public IPrintable {
public:
    explicit Sign(char sym = 0) : sym_(sym) {}
    
    void Print (PrinterPtr printer) const override {
        printer->Print(sym_);
    }
private:
    char sym_;
};