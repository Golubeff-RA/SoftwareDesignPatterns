#include <iostream>

#include "auditory.h"

int main() {
    HumanPtr teacher(new Teacher("Starostin Nikolai Vladimirovich", "Hello world!"));
    HumanPtr st1(new Student("Roman"));
    HumanPtr st2(new Student("Daniil"));
    HumanPtr st3(new Student("Vladimir"));
    HumanPtr st4(new Student("Maksim"));
    HumanPtr st5(new Student("Sasha"));
    HumanPtr st6(new Student("Nikita"));
    HumanPtr st7(new NikitaStudent());

    Auditory auditory("112");
    auditory.AddHuman(teacher);
    auditory.AddHuman(st1);
    auditory.AddHuman(st2);
    auditory.AddHuman(st4);
    auditory.AddHuman(st5);
    auditory.AddHuman(st6);
    auditory.AddHuman(st7);

    HumanPtr auditory_zoom(new Auditory("zoom"));
    std::dynamic_pointer_cast<Auditory>(auditory_zoom)->AddHuman(st3);
    auditory.AddHuman(auditory_zoom);

    auto result = auditory.StartLection();
    if (result.has_value()) {
        std::cout << "Lecture completed! Total syms sayed: " << result.value() << std::endl;
        std::cout << st3->GetName()
                  << " writed: " << std::dynamic_pointer_cast<Student>(st3)->GetNotebook()
                  << std::endl;
        std::cout << st7->GetName()
                  << " writed: " << std::dynamic_pointer_cast<Student>(st7)->GetNotebook()
                  << std::endl;
    } else {
        std::cout << result.error();
    }

    return 0;
}