#pragma once
#include "human.h"

class Teacher : public Human {
public:
    Teacher(const std::string& name, const std::string& lecture)
        : Human(name), lecture_(lecture), iter_(lecture_.begin()) {}

    SpeakResult Speak() override {
        if (iter_ == lecture_.end()) {
            return std::nullopt;
        }

        return *(iter_++);
    }

    void Listen(SpeakResult sym) override {}

private:
    std::string lecture_;
    std::string::const_iterator iter_;
};