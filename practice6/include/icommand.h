#pragma once
#include <memory>

class ICommand;

using CommandPtr = std::unique_ptr<ICommand>;

class ICommand {
public:
    virtual void Execute(bool should_register = true) = 0;
    virtual ~ICommand() = default;
    virtual CommandPtr clone() const = 0;
};
