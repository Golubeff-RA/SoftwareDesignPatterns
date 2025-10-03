#pragma once
#include <list>

#include "human.h"

class Student : public Human {
public:
    explicit Student(const std::string& name) : Human(name) {}

    void Listen(SpeakResult sym) override {
        if (sym.has_value()) { 
            notebook_.push_back(sym.value()); 
        }
    }

    SpeakResult Speak() override { return std::nullopt; }

    virtual std::string GetNotebook() const {
        std::string result;
        result.reserve(notebook_.size());
        for (char sym : notebook_) {
            result.push_back(sym);
        }

        return result;
    }

private:
    std::list<char> notebook_;
};

class NikitaStudent : public Student {
public:
    NikitaStudent() : Student("Nikita") {}

    void Listen(SpeakResult sym = 0) override {}

    std::string GetNotebook() const override {
        return std::string("I am Nikita. I know everything :-)");
    }
};
