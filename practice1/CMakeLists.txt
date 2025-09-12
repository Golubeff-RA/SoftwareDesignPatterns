file(GLOB_RECURSE LIBRARY_SRC CONFIGURE_DEPENDS "src/*.cpp")
add_library(PrinterLIB ${LIBRARY_SRC})

target_include_directories(PrinterLIB PUBLIC include)

add_executable(practice1 main.cpp)
target_include_directories(practice1 PUBLIC include)
target_link_libraries(practice1 PRIVATE PrinterLIB)