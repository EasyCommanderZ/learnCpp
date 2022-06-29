#include "testThreadPool.h"
#include <ThreadPool.h>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>

using tp = std::chrono::system_clock::time_point;
using td = std::chrono::system_clock::duration;

ThreadPool tpool;


void testPool() {
    

    for (int i = 0; i < 2000; i++) {
        tpool.addTask([&] {
            std::stringstream ss;
            ss << i << " ";
            std::cout << ss.str();
        });
    }

    return;
}

void testNomal() {
    for (int i = 0; i < 2000; i++) {
        std::stringstream ss;
        ss << i << " ";
        std::cout << ss.str();
    }
    return;
}

void benchmark() {
    tp start_time1 = std::chrono::system_clock::now();
    testPool();
    tp end_time1 = std::chrono::system_clock::now();
    td duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - start_time1);

    tp start_time2 = std::chrono::system_clock::now();
    testPool();
    tp end_time2 = std::chrono::system_clock::now();
    td duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - start_time2);

    std::cout << "Thread Pool : " << duration1.count() << std::endl;
    std::cout << "Normal : " << duration2.count() << std::endl;
}