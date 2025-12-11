#include <functional>
#include <iostream>

#include "collection.h"
#include "complex_num.h"
#include "sorting_strategy.h"

template <CanCompare Strategy>
void Pipeline(ComplexNumCollection coll, std::string name_of_pipeline) {
    std::cout << "\n===============================\n"
              << name_of_pipeline << std::endl;
    std::cout << "Original collection:\n";
    for (size_t i = 0; i < coll.Size(); ++i) {
        std::cout << coll[i] << std::endl;
    }

    coll.Sort<Strategy>();
    std::cout << "\nSorted collection:\n";
    for (size_t i = 0; i < coll.Size(); ++i) {
        std::cout << coll[i] << std::endl;
    }
    std::cout << "===============================\n";
}

int main() {
    ComplexNumCollection coll({{12, 34},
                               {54, 12},
                               {123, 43},
                               {123, 87},
                               {1342, 1244},
                               {1234, 435},
                               {324, 324},
                               {341, 43},
                               {124, 2312},
                               {124, 231}});
    Pipeline<FirstStrategy>(coll, "Возрастание Re");
    Pipeline<SecondStrategy>(coll, "Возрастание Im");
    Pipeline<InverseDecorator<FirstStrategy>>(coll, "Убывание Re");
    Pipeline<InverseDecorator<SecondStrategy>>(coll, "Убывание Im");

    double sum_real = 0;
    double sum_im = 0;
    std::function<void(ComplexNumber&, double&, double&)> summ{
        [](ComplexNumber& num, double& sum_real, double& sum_im) {
            sum_real += num.real;
            sum_im += num.im;
        }};

    coll.ForEach(summ, sum_real, sum_im);
    return 0;
}