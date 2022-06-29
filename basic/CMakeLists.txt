file(GLOB sources *.cpp)

add_library(basic SHARED ${sources})
target_include_directories(basic PUBLIC .)