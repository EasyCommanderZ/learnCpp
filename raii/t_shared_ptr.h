#ifndef __RAII_T_SHARED_PTR_H_
#define __RAII_T_SHARED_PTR_H_

#include <atomic>
#include <iostream>
#include <ostream>
// 不可拷贝基类
class noncopyable {
public:
    noncopyable(const noncopyable &) = delete;
    noncopyable operator=(const noncopyable &) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

// 引用计数控制块
class refCount : noncopyable {
private:
    std::atomic_int _cnt;

public:
    refCount() {
        _cnt.store(0);
    }

    refCount(int cnt) {
        _cnt.store(cnt);
    }

    void decRefCount() {
        _cnt.fetch_sub(1);
    }

    void incRefCount() {
        _cnt.fetch_add(1);
    }

    int getRefCount() {
        return _cnt.load();
    }
};

// 简易版shared_ptr模版类
template <typename T>
class t_shared_ptr : noncopyable {
public:
    using value_type = T;
    using pointer_type = T *;
    using reference_type = T &;
    // constructor
    t_shared_ptr() :
        _ptr(nullptr), _ref(nullptr){};
    t_shared_ptr(pointer_type ptr) :
        _ptr(ptr), _ref(new refCount(1)){};
    t_shared_ptr(const t_shared_ptr &other) {
        _ptr = other._ptr;
        _ref = other._ref;
        this->increase();
    }
    // copy constructor
    t_shared_ptr &operator=(const t_shared_ptr other) {
        if (this == &other) return *this;
        this->decrease();
        _ptr = other._ptr;
        _ref = other._ref;
        this->increase();
    }

    // deconstructor
    ~t_shared_ptr() {
        std::cout << "t_shared_ptr decreased " << std::endl;
        decrease();
    }

    int use_count() {
        return _ref->getRefCount();
    }

    // Dereferences the stored pointer. The behavior is undefined if the stored pointer is null
    pointer_type operator->() {
        return this->_ptr;
    }

    reference_type operator*() {
        return *(this->_ptr);
    }

    pointer_type get() {
        return this->_ptr;
    }

    operator bool() {
        return this->_ptr != nullptr;
    }

private:
    // 指向控制块的指针，记录引用计数
    refCount *_ref;
    // 指向共享资源的指针
    pointer_type _ptr;

    void decrease() {
        if (_ptr == nullptr) return;
        _ref->decRefCount();
        if (_ref->getRefCount() == 0) {
            delete _ptr;
            std ::cout << "ref count becomes 0, free resource" << std ::endl;
        }
    }

    void increase() {
        if (_ptr == nullptr) return;
        _ref->incRefCount();
    }
};

class t_ptr_Resource {
private:
    int _val;

public:
    t_ptr_Resource operator=(t_ptr_Resource &res) = delete;
    t_ptr_Resource() = default;
    t_ptr_Resource(int val) :
        _val(val){};

    int getV() const {
        return _val;
    };

    void setV(int val) {
        std ::cout << "Resource change val from " << _val << " to " << val << std::endl;
        this->_val = val;
    };
};

std::ostream &operator<<(std::ostream &out, const t_ptr_Resource &res) {
    out << res.getV();
    return out;
};

void test_shared_ptr();

#endif /* __RAII_T_SHARED_PTR_H_ */
