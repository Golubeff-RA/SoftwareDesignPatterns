#pragma once
#include <algorithm>
#include <initializer_list>
#include <vector>

#include "complex_num.h"
#include "sorting_strategy.h"

class ComplexNumCollection {
public:
    ComplexNumCollection(std::initializer_list<ComplexNumber> data)
        : data_(data){};

    size_t Size() { return data_.size(); }

    void Append(ComplexNumber num) { data_.push_back(num); }

    ComplexNumber operator[](size_t idx) const { return data_.at(idx); }

    ComplexNumber& operator[](size_t idx) { return data_.at(idx); }

    void Sort(SortStrategyPtr sorter) {
        std::sort(data_.begin(), data_.end(),
                  [&](const ComplexNumber& left, const ComplexNumber& right) {
                      return (*sorter)(left, right);
                  });
    }

private:
    std::vector<ComplexNumber> data_;
};