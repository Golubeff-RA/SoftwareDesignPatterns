#pragma once
#include <iprinter.h>

class IPrintable {
public:
    virtual void Print(PrinterPtr printer) const = 0;
};

using PrintablePtr = std::shared_ptr<IPrintable>;

class Word : public IPrintable {
public:
    explicit Word(const std::string& data);

    explicit Word(std::string&& data);

    void Print(PrinterPtr printer) const override;

private:
    std::string data_;
};

class Sign : public IPrintable {
public:
    explicit Sign(char sym = 0);

    void Print(PrinterPtr printer) const override;

private:
    char sym_;
};