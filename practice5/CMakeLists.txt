add_executable(practice5 main.cpp)
target_include_directories(practice5 PUBLIC include ${CMAKE_SOURCE_DIR}/practice2/include ${CMAKE_SOURCE_DIR}/practice4/include)