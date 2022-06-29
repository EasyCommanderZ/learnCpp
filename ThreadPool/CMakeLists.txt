file(GLOB sources *.cpp)

add_library(ThreadPool SHARED ${sources})
find_package(Threads REQUIRED)
target_include_directories(ThreadPool PUBLIC .)