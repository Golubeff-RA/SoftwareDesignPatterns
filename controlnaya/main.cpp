#include <iostream>

#include "i_number_seq.h"
int main() {
    EulerSeq euler;
    euler.PrintFirstNNums(20, std::cout);
    NegativeDecorator negative_euler(NumberSeqPtr(new FibonacciSeq()));
    std::cout << std::endl;
    negative_euler.PrintFirstNNums(20, std::cout);
    SumOfSeqs sum_decorator(
        {NumberSeqPtr(new NegativeDecorator(NumberSeqPtr(new FibonacciSeq))),
         NumberSeqPtr(new EulerSeq)});
    std::cout << std::endl;
    sum_decorator.PrintFirstNNums(20, std::cout);
    std::cout << std::endl;
    return 0;
}