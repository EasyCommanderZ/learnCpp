#include <functional>
#include <iostream>
#include <cstdint>

// using namespace std;
// # define TRIGGER
#include <basic.h>
#include <advanced.h>
#include <enumType.h>
#include <classes.h>

#include <stackUnwinding.h>
#include <t_shared_ptr.h>
#include <t_unique_lock.h>
#include <testClasses.h>
#include <testThreadPool.h>
#include <CAS.h>
#include <thread>

using std::cout;
using std::endl;

int main() {
    // test_shared_ptr();
    // test_unique_lock();
    // testConstRef();
    // benchmark();
    std::thread t(CASBenchmark);
    t.join();
    // cout << "?" << std::endl;
    return 0;
}