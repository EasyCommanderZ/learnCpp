file(GLOB sources *.cpp)

add_library(advanced SHARED ${sources})
target_include_directories(advanced PUBLIC .)