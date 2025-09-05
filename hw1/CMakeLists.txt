
add_executable(hw1_main main.cpp)

file(GLOB_RECURSE LIBRARY_SRC CONFIGURE_DEPENDS "src/*.cpp")
add_library(UniversityLIB ${LIBRARY_SRC})

target_include_directories(UniversityLIB PUBLIC include)
target_include_directories(hw1_main PUBLIC include)
target_link_libraries(hw1_main PRIVATE UniversityLIB)
