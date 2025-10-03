#pragma once
#include <string>
#include <optional>
#include <memory>

using SpeakResult = std::optional<char>;

class Human {
public:
    explicit Human(const std::string& name) : name_(name) {}

    std::string GetName() const { return name_; }

    virtual void Listen(SpeakResult sym = 0) = 0;

    virtual SpeakResult Speak() = 0;

    virtual ~Human() {}

private:
    std::string name_;
};

using HumanPtr = std::shared_ptr<Human>;