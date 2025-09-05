#pragma once
#include "human.h"
#include "optional"

using TalkResult = std::optional<char>;

class Teacher : public IHuman {
public:
    Teacher(const std::string& name, const std::string& lecture)
        : IHuman(name), lecture_(lecture), iter_(lecture_.begin()) {}

    TalkResult Talk() {
        if (iter_ == lecture_.end()) {
            return std::nullopt;
        }

        return *(iter_++);
    }

private:
    std::string lecture_;
    std::string::const_iterator iter_;
};