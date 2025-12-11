#include <iostream>
#include <memory>

#include "collection.h"
#include "complex_num.h"
#include "sorting_strategy.h"

void Pipeline(ComplexNumCollection coll, SortStrategyPtr sorter,
              std::string name_of_pipeline) {
    std::cout << "\n===============================\n"
              << name_of_pipeline << std::endl;
    std::cout << "Original collection:\n";
    for (size_t i = 0; i < coll.Size(); ++i) {
        std::cout << coll[i] << std::endl;
    }

    coll.Sort(sorter);
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
    SortStrategyPtr sorter_1 = std::make_shared<FirstStrategy>();
    SortStrategyPtr sorter_2 = std::make_shared<SecondStrategy>();
    Pipeline(coll, sorter_1, "Возрастание Re");
    Pipeline(coll, sorter_2, "Возрастание Im");

    SortStrategyPtr inv_sorter_1 = std::make_shared<InverseDecorator>(sorter_1);
    SortStrategyPtr inv_sorter_2 = std::make_shared<InverseDecorator>(sorter_2);
    Pipeline(coll, inv_sorter_1, "Убывание Re");
    Pipeline(coll, inv_sorter_2, "Убывание Im");

    return 0;
}