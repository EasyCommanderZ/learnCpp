file(GLOB sources *.cpp)

add_library(CAS SHARED ${sources})
find_package(Threads REQUIRED)
target_include_directories(CAS PUBLIC .)