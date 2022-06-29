cmake_minimum_required(VERSION 3.10)

project(Learn_CPP)

file(GLOB sources main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(basic)
add_subdirectory(advanced)
add_subdirectory(raii)
add_subdirectory(ThreadPool)
add_subdirectory(CAS)

add_executable(main ${sources})
# find_package(Threads REQUIRED)
target_link_libraries(main PUBLIC basic advanced raii ThreadPool CAS)
