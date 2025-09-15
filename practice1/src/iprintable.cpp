#include <iprintable.h>

Word::Word(const std::string& data) : data_(data) {}

Word::Word(std::string&& data) : data_(data) {}

void Word::Print(PrinterPtr printer) const { printer->Print(data_); }

Sign::Sign(char sym) : sym_(sym) {}

void Sign::Print(PrinterPtr printer) const { printer->Print(sym_); }