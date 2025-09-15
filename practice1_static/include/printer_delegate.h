#pragma once

#include <printer.h>
#include <printable.h>

template <class Printer>
class PrinterDelegate {
public:
    template <class Printable>
    void Print(Printable obj) const {
        
    }
};