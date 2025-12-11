#pragma once
#include <memory>

#include "command_manager.h"
#include "icommand.h"
#include "initializers/matrix_initializer.h"
#include "matrix/imatrix.h"

using namespace my_math_lib;

template <typename Derived>
class ACommand : public ICommand {
protected:
    virtual void DoExecute() = 0;

public:
    void Execute(bool should_register = true) override {
        DoExecute();
        if (should_register) {
            CommandManager::Instance()->Register(clone());
        }
    }

private:
    CommandPtr clone() const override {
        return std::make_unique<Derived>(static_cast<const Derived&>(*this));
    }
};

class InitAppCommand : public ACommand<InitAppCommand> {
protected:
    void DoExecute() override { MatrixZeroer::ZeroMatrix(matrix_); }

public:
    InitAppCommand(MatrixPtr<double> matrix) : matrix_(matrix) {}

private:
    MatrixPtr<double> matrix_;
};

class SetMatrixValueCommand : public ACommand<SetMatrixValueCommand> {
private:
    MatrixPtr<double> matrix_;
    size_t row_ = 0;
    size_t col_ = 0;
    double value_ = 0;

protected:
    void DoExecute() override { (*matrix_)[row_, col_] = value_; }

public:
    SetMatrixValueCommand(MatrixPtr<double> matrix, size_t row, size_t col,
                          double value)
        : matrix_(matrix), row_(row), col_(col), value_(value) {}
};