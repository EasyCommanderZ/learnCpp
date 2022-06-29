#include "t_shared_ptr.h"
#include "t_unique_lock.h"
#include "testClasses.h"
#include<iostream>
#include <sys/_pthread/_pthread_mutex_t.h>
#include<thread>
#include<atomic>
#include<mutex>
using std::cout;
using std::endl;

// ------------------ test shared pointer
void test_shared_ptr() {
    t_shared_ptr<t_ptr_Resource> sp(new t_ptr_Resource(17));
    auto nsp = sp;
    cout << sp->getV() << endl;
    cout << nsp->getV() << endl;
    cout << (*nsp).getV() << endl;
    cout << nsp.use_count() << endl;

    if(nsp) {
        nsp.get() -> setV(18);
        auto p = nsp.get();
        cout << "*p = " << (*p) << endl;
        cout << sp.use_count()<< endl;
    }
    return ;
};

// ----------------- test unique lock
std::mutex mtx;
std::atomic<bool> isOdd(true); // 先打印奇数

void printOdd() {
    for(int i = 1; i <= 20; i += 2) {
        bool odd = true;
        while(isOdd.compare_exchange_weak(odd, odd) == false) { odd = true;}
        t_unique_lock lock(mtx);
        cout << i << " ";
        isOdd = false;
    }
}

void printEven() {
    for(int i = 2; i <= 20; i += 2) {
        bool odd = false;
        while(isOdd.compare_exchange_weak(odd, odd) == false) {
            odd = false;
        }
        t_unique_lock lock(mtx);
        cout << i << (i == 20 ? "\n" : " ");
        isOdd = true; // next step is print next odd numebr
    }
}

void test_unique_lock() {
    // 一个简单的双线程奇偶交替打印程序， 使用 CAS 和 mutex
    std::thread oddThread(printOdd);
    std::thread evenThread(printEven);

    oddThread.join();
    evenThread.join();
};

// ----
void showCatName(Cat const& cat) {
    cat.getName();
}

void testConstRef() {
    Cat a("Easy");
    a.getName();
    showCatName(a);
}