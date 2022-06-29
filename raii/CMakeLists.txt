file(GLOB sources *.cpp)

add_library(raii SHARED ${sources})
target_include_directories(raii PUBLIC .)