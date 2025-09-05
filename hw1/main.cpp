#include <iostream>
#include "auditory.h"

int main() {
    TeacherPtr teacher(new Teacher("Starostin Nikolai Vladimirovich", "Hello world!"));
    StudentPtr st1(new IStudent("Roman"));
    StudentPtr st2(new IStudent("Daniil"));
    StudentPtr st3(new IStudent("Vladimir"));
    StudentPtr st4(new IStudent("Maksim"));
    StudentPtr st5(new IStudent("Sasha"));
    StudentPtr st6(new IStudent("Nikita"));
    StudentPtr st7(new NikitaStudent());

    Auditory auditory(112);
    auditory.SetTeacher(teacher);
    auditory.AddStudent(st1);
    auditory.AddStudent(st2);
    auditory.AddStudent(st3);
    auditory.AddStudent(st4);
    auditory.AddStudent(st5);
    auditory.AddStudent(st6);
    auditory.AddStudent(st7);

    auto result = auditory.StartLection();
    if (result.has_value()) {
        std::cout << "Lecture completetd! Total syms sayed: " << result.value() << std::endl;
        std::cout << st3->GetName() << " writed: " << st3->GetNotebook() << std::endl;
        std::cout << st7->GetName() << " writed: " << st7->GetNotebook() << std::endl;
    } else {
        std::cout << result.error();
    }


    return 0;
}