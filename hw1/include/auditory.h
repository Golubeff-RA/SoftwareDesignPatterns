#pragma once
#include <expected>
#include <memory>

#include "student.h"
#include "teacher.h"

using StudentPtr = std::shared_ptr<IStudent>;
using TeacherPtr = std::shared_ptr<Teacher>;
// результат лекции, если всё ок, то вернёт число прочитанных символов, иначе строку с ошибкой
using LectureResult = std::expected<size_t, std::string>;

class Auditory {
public:
    Auditory(size_t number = 0) : number_(number) {}

    void SetTeacher(TeacherPtr teacher) { teacher_ = teacher; }

    void AddStudent(StudentPtr student) { students_.push_back(student); }

    bool DelStudent(const std::string& name) {
        for (auto it = students_.begin(); it != students_.end(); ++it) {
            if ((*it)->GetName() == name) {
                students_.erase(it);
                return true;
            }
        }

        return false;
    }

    size_t GetNumber() const { return number_; }

    std::list<StudentPtr> GetStutents() const { return students_; }

    LectureResult StartLection() {
        size_t sym_cnt = 0;
        try {
            for (auto teacher_says = teacher_->Talk(); teacher_says != std::nullopt;
                 teacher_says = teacher_->Talk()) {
                ++sym_cnt;
                for (auto& stud : students_) {
                    stud->Listen(teacher_says.value());
                }
            }
        } catch (...) {
            return std::unexpected("Something went wrong in auditory " + std::to_string(number_));
        }

        return sym_cnt;
    }

private:
    size_t number_;
    std::list<StudentPtr> students_;
    TeacherPtr teacher_ = nullptr;
};