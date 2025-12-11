#pragma once
#include <algorithm>
#include <initializer_list>
#include <utility>
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

    template <CanCompare Strategy>
    void Sort() {
        std::sort(data_.begin(), data_.end(), Strategy::operator());
    }

    template <typename Func, typename... Args>
    void ForEach(Func pred, Args&&... args) {
        for (auto& num : data_) {
            pred(num, std::forward<Args>(args)...);
        }
    }

private:
    std::vector<ComplexNumber> data_;
};