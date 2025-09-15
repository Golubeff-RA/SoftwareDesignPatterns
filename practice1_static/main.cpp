#include <printable.h>
#include <printer.h>

int main() {
    Text text(IPrintable("Testing"), IPrintable(' '), IPrintable("of"), IPrintable(' '),
              IPrintable("my"), IPrintable(' '), IPrintable("architecture"), IPrintable('!'));
    text.PrintText<PrinterDefault, 0>();
    std::cout << std::endl;
    text.PrintText<PrinterWithScobes, 0>();
    std::cout << std::endl;
    text.PrintText<PrinterWithEndl, 0>();
    return 0;
}