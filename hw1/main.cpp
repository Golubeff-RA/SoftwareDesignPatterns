#include <iostream>

#include "auditory.h"

void Scenary() {
    HumanPtr teacher(new Teacher("Starostin Nikolai Vladimirovich", "Hello world!"));
    HumanPtr roman(new Student("Roman"));
    HumanPtr daniil(new Student("Daniil"));
    HumanPtr vladimir(new Student("Vladimir"));
    HumanPtr maksim(new Student("Maksim"));
    HumanPtr sasha(new Student("Sasha"));
    HumanPtr nikita(new Student("Nikita"));
    HumanPtr nikita_2(new NikitaStudent());

    Auditory auditory("112");
    auditory.AddHumans({teacher, roman, daniil, maksim, sasha, nikita, nikita_2});

    HumanPtr auditory_zoom(new Auditory("zoom"));
    std::dynamic_pointer_cast<Auditory>(auditory_zoom)->AddHuman(vladimir);
    auditory.AddHuman(auditory_zoom);

    auto result = auditory.StartLection();
    if (result.has_value()) {
        std::cout << "Lecture completed! Total syms sayed: " << result.value() << std::endl;
        for (const auto& student : {roman, vladimir, daniil, maksim, sasha, nikita, nikita_2}) {
            std::cout << student->GetName()
                  << " writed: " << std::dynamic_pointer_cast<Student>(student)->GetNotebook()
                  << std::endl;
        }
    } else {
        std::cout << result.error();
    }
}


int main() {
    Scenary();
    return 0;
}