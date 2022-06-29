#ifndef __ADVANCED_CLASSES_H_
#define __ADVANCED_CLASSES_H_
#include <cassert>
#include <initializer_list>
#include<iostream>
class IntArray {
private:
    int m_length;
    int *m_data;

public:
    IntArray() = default;

    IntArray(int length) :
        m_length(length) {
        assert(length >= 0);
        if (length > 0) {
            m_data = new int[length]{};
        }
    };

    IntArray(std::initializer_list<int> list) : IntArray(static_cast<int>(list.size())) {
        int i = 0;
        for(auto v : list) {
            m_data[i] = v;
            i ++;
        }
    }

    ~IntArray() {
        delete[] m_data;
    }

    void erase() {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int &operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() const {
        return m_length;
    }

    void reallocate(int newLength) {
        // First we delete any existing elements
        erase();

        // If our array is going to be empty now, return here
        if (newLength <= 0)
            return;

        // Then we have to allocate new elements
        m_data = new int[newLength];
        m_length = newLength;
    }


};

class Base
{
public:
    int m_public {}; // can be accessed by anybody
protected:
    int m_protected {}; // can be accessed by Base members, friends, and derived classes
private:
    int m_private {}; // can only be accessed by Base members and friends (but not derived classes)
};

class Derived: public Base
{
public:
    Derived()
    {
        m_public = 1; // allowed: can access public base members from derived class
        m_protected = 2; // allowed: can access protected base members from derived class
        // m_private = 3; // not allowed: can not access private base members from derived class
    }
};

class Resource{
    public:
    Resource(){std::cout << "Reousrce created" << std::endl; };
    ~Resource(){std::cout<< "Resource dstroyed" << std::endl; };
};

template<typename T>
class Auto_ptr {
private:
    T* ptr;
public: 
    Auto_ptr(T* o_ptr = nullptr) : ptr(o_ptr) {};
    ~Auto_ptr() {delete ptr;}

    T& operator*() const {return *ptr;};
    T* operator->() const {return ptr;};
};


#endif /* __ADVANCED_CLASSES_H_ */
