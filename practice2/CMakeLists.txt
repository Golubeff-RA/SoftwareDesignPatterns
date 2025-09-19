file(GLOB_RECURSE LIBRARY_SRC CONFIGURE_DEPENDS "src/*.cpp")
add_library(mathLIB ${LIBRARY_SRC})

target_include_directories(mathLIB PUBLIC include)

add_executable(practice2 main.cpp)
target_include_directories(practice1 PUBLIC include)
target_link_libraries(practice2 PRIVATE mathLIB)