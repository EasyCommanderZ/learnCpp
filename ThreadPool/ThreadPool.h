#ifndef __THREADPOOL_THREADPOOL_H_
#define __THREADPOOL_THREADPOOL_H_

#include "MTQueue.h"
#include <atomic>
#include <cstddef>
#include <functional>
#include <i386/limits.h>
#include <stdexcept>
#include <thread>
#include <vector>
class ThreadPool {
public:
    using task_t = std::function<void()>;

    void InitializeWorkers(size_t workers_num) {
        for (size_t i = 0; i < workers_num; i++) {
            std::thread t([&]() {
                while (this->_running) {
                    auto task = this->_task_queue.pop();
                    if (task) task();
                }
            });
            this->_workers.push_back(std::move(t));
        }
    }

    explicit ThreadPool(size_t workers_num = std::thread::hardware_concurrency()) {
        InitializeWorkers(workers_num);
    }

    void addTask(task_t t) {
        if (not this->_running) {
            throw ::std::runtime_error("Thread pool already stopped.");
        }
        this->_task_queue.push_back(std::move(t));
    }

    void stop() {
        this->_running = false;

        for(std::size_t i = 0; i < this->_workers.size(); i ++) {
            this -> _task_queue.push_back(nullptr);
        }

        for (auto &w : _workers) {
            w.join();
        }
    }

    ~ThreadPool() {
        if (this->_running) {
            stop();
        }
    }

private:
    std::atomic_bool _running{true};
    MTQueue<task_t> _task_queue;
    std::vector<std::thread> _workers;
};

#endif /* __THREADPOOL_THREADPOOL_H_ */
