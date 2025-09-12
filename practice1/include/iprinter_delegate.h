#include <iprinter.h>
#include <iprintable.h>

class IPrinterDelegate : public IPrinter {
public:
    virtual void Print(PrintablePtr printable) = 0;

    void Print(const std::string& str) override {
    }

    void Print(char) override {
    }
};

class PrinterDelegate : public IPrinterDelegate {
public:
    void Print(PrintablePtr printable) override {
        printable->Print(PrinterPtr(new PrinterSpecial()));
    }
};