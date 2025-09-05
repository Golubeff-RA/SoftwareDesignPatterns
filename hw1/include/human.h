#pragma once
#include <string>

class IHuman {
public:
    explicit IHuman(const std::string& name) : name_(name) {}

    std::string GetName() const { return name_; }

private:
    std::string name_;
};