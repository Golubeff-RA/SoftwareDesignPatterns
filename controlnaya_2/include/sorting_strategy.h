#pragma once
#include <memory>

#include "complex_num.h"

class ISortingStrategy {
public:
    virtual bool operator()(const ComplexNumber& left,
                            const ComplexNumber& right) const = 0;
    virtual ~ISortingStrategy() = default;
};

using SortStrategyPtr = std::shared_ptr<ISortingStrategy>;

class FirstStrategy : public ISortingStrategy {
public:
    bool operator()(const ComplexNumber& left,
                    const ComplexNumber& right) const override {
        return left.real < right.real;
    }
};

class SecondStrategy : public ISortingStrategy {
public:
    bool operator()(const ComplexNumber& left,
                    const ComplexNumber& right) const override {
        return left.im < right.im;
    }
};

class InverseDecorator : public ISortingStrategy {
public:
    InverseDecorator(SortStrategyPtr sorter) : sorter_(sorter) {}
    bool operator()(const ComplexNumber& left,
                    const ComplexNumber& right) const override {
        return !(*sorter_)(left, right);
    }

private:
    SortStrategyPtr sorter_;
};
