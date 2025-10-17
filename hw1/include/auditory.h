#pragma once
#include <expected>

#include "student.h"
#include "teacher.h"

using LectureResult = std::expected<size_t, std::string>;

class Auditory : public Human{
public:
    Auditory(const std::string& name) : Human(name) {}

    SpeakResult Speak() { return std::nullopt; }

    void Listen(SpeakResult sym)  {
        for (auto& human : humans_) {
            human->Listen(sym);
        }
    }

    void AddHumans(std::initializer_list<HumanPtr> human_ptrs) {
        for (auto human_ptr : human_ptrs) {
            humans_.push_back(human_ptr);
        }
    }

    void AddHuman(HumanPtr human_ptr) { humans_.push_back(human_ptr); }

    bool DelHuman(const std::string& name) {
        for (auto it = humans_.begin(); it != humans_.end(); ++it) {
            if ((*it)->GetName() == name) {
                humans_.erase(it);
                return true;
            }
        }

        return false;
    }

    LectureResult StartLection() {
        size_t cnt_sended = 0;
        bool non_nullopt = false;
        try {
            do {
                non_nullopt = false;
                for (auto& human : humans_) {
                    SpeakResult res = human->Speak();
                    if (res.has_value()) {
                        non_nullopt = true;
                        ++cnt_sended;
                    }
                    Listen(res);
                }
            } while (non_nullopt);
        } catch (...) {
            return std::unexpected("Something went wrong during the lection :(");
        }

        return LectureResult(cnt_sended);
    }

private:
    std::list<HumanPtr> humans_;
};