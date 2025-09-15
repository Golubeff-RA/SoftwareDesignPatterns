#include <iprintable.h>
#include <iprinter.h>
#include <iprinter_delegate.h>
#include <text.h>

int main() {
    Text text{std::list{PrintablePtr(new Word("Тестируем")), PrintablePtr(new Sign(' ')),
                        PrintablePtr(new Word("мою")), PrintablePtr(new Sign(' ')),
                        PrintablePtr(new Word("архитектуру")), PrintablePtr(new Sign('!'))}};
    text.Print(PrinterPtr(new PrinterDefault()));

    std::cout << std::endl;
    text.Print(PrinterPtr(new PrinterSpecial()));

    std::cout << std::endl;
    PrinterDelegate p;
    p.Print(PrintablePtr(
        new Text{std::list{PrintablePtr(new Word("Тестируем")), PrintablePtr(new Sign(' ')),
                           PrintablePtr(new Word("мою")), PrintablePtr(new Sign(' ')),
                           PrintablePtr(new Word("архитектуру")), PrintablePtr(new Sign('!'))}}));

    Text2 text2(PrintablePtr(new Word("Тестируем")), PrintablePtr(new Sign(' ')),
                PrintablePtr(new Word("мою")), PrintablePtr(new Sign(' ')),
                PrintablePtr(new Word("архитектуру")), PrintablePtr(new Sign('!')));
    text2.Print(PrinterPtr(new PrinterDefault()));
    return 0;
}