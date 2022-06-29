#ifndef __RAII_T_UNIQUE_LOCK_H_
#define __RAII_T_UNIQUE_LOCK_H_

#include <mutex>
#include <iostream>
#include<t_shared_ptr.h>

class t_unique_lock : noncopyable {
private:
    std::mutex &_mtx;
    bool _own;

public:
    t_unique_lock(std::mutex &mtx) :
        _mtx(mtx), _own(false) {
        _mtx.lock();
        _own = true;
    }

    void lock() {
        if (!_own) {
            _mtx.lock();
            _own = true;
        }
    }

    void unlock() {
        if (_own) {
            _mtx.unlock();
            _own = false;
        }
    }

    ~t_unique_lock() {
        if (_own) {
            // std::cout << "deconstruct" << std::endl;
            _mtx.unlock();
        }
    }
};

void test_unique_lock();

#endif /* __RAII_T_UNIQUE_LOCK_H_ */
