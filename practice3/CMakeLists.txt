
file(GLOB_RECURSE LIBRARY_SRC CONFIGURE_DEPENDS "src/*.cpp")
add_library(drawingLIB ${LIBRARY_SRC})

target_include_directories(drawingLIB PUBLIC include ${CMAKE_SOURCE_DIR}/practice2/include)
target_link_libraries(drawingLIB PUBLIC imgui OpenGL::GL glfw)

add_executable(practice3 main.cpp)
target_include_directories(practice3 PUBLIC include ${CMAKE_SOURCE_DIR}/practice4/include)
target_link_libraries(practice3 PRIVATE drawingLIB)