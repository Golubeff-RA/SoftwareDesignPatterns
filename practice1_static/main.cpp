#include <printable.h>
#include <printer.h>

int main() {
    Text text(IPrintable("Testing"), IPrintable(' '), IPrintable("of"), IPrintable(' '),
              IPrintable("my"), IPrintable(' '), IPrintable("architecture"), IPrintable('!'));
    text.Print<PrinterDefault>();
    std::cout << std::endl;
    text.Print<PrinterWithScobes>();
    std::cout << std::endl;
    text.Print<PrinterWithEndl>();
    return 0;
}