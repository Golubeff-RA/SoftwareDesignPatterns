#pragma once

#include <string>
#include <iostream>
#include <memory>

class IPrinter {
public:
    virtual void Print(const std::string& data) = 0;
    virtual void Print(char sym) = 0;
};

using PrinterPtr = std::shared_ptr<IPrinter>;

class PrinterDefault: public IPrinter {
public:
    void Print(const std::string& data) override {
        std::cout << data;
    }

    void Print(char sym) override {
        std:: cout << sym;
    }
};

class PrinterSpecial: public PrinterDefault {
public:
    void Print(const std::string& data) override {
        std::cout << '(' << data << ')';
    }
    
};