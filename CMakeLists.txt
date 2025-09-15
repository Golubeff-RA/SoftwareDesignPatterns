cmake_minimum_required(VERSION 3.5.0)

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wsign-compare")

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all -O2"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

set(CMAKE_CXX_FLAGS_TSAN "-g -fsanitize=thread -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in tsan build"
    FORCE)

set(CMAKE_CXX_FLAGS_REL "-O2 -DNDEBUG" 
    CACHE STRING "Compiler flags for the release version" 
    FORCE)

message("General compiler flags: " ${CMAKE_CXX_FLAGS})
message("Debug build compiler flags: " ${CMAKE_CXX_FLAGS_DEBUG})
message("ASAN build compiler flags: " ${CMAKE_CXX_FLAGS_ASAN})
message("TSAN build compiler flags: " ${CMAKE_CXX_FLAGS_TSAN})
message("Release build compiler flags: " ${CMAKE_CXX_FLAGS_REL})

add_subdirectory(hw1)
add_subdirectory(practice1)
add_subdirectory(practice1_static)