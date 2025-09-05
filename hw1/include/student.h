#pragma once
#include <list>

#include "human.h"

class IStudent : public IHuman {
public:
    explicit IStudent(const std::string& name) : IHuman(name) {}
    virtual void Listen(char sym = 0) { notebook_.push_back(sym); }

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

class NikitaStudent : public IStudent {
public:
    NikitaStudent() : IStudent("Nikita") {}
    void Listen(char sym = 0) override {}

    std::string GetNotebook() const override { return std::string("I am Nikita. I know everything :-)"); }
};
