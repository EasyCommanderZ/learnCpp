#ifndef __ADVANCED_ADVANCED_H_
#define __ADVANCED_ADVANCED_H_
#include <__iterator/counted_iterator.h>
#include <functional>
#include <iostream>
#include <ostream>

template <typename T>
struct Pair {
    T first;
    T second;
};

template <typename T>
const T max(Pair<T> p) {
    return p.first > p.second ? p.first : p.second;
}

int ret5();

using cmpF = std::function<bool(int, int)>;

bool isEqual(int x, int y, cmpF);
// bool isEqual(int x, int y, bool(*cmp)(int, int));

bool EqualInARange(int x, int y);

class testClass1 {
private:
    int x = 0;
    int y = 0;
    int z = 0;

public:
    testClass1() = default;

    testClass1(int v1, int v2, int v3) {
        this->x = v1, this->y = v2, this->z = v3;
    };
    int getX() {
        return this->x;
    };
    void printClass() {
        std :: cout << x << " " << y << " " << z << std::endl;
    };
};

class Something {
    private:
    static inline int s_value = 1;
    public:
    static int getValue(){ return s_value ++; };
};


class Cents
{
private:
    int m_cents {};

public:
    // constructor
    Cents(int cents) : m_cents { cents } { };
    // copy constructor
    Cents(Cents& a) : m_cents(a.m_cents) {
        std :: cout << "copy" << std :: endl;
    };


    friend int operator+(Cents&c , int v);
    Cents operator+(Cents& b) {
        return {m_cents + b.m_cents};
    }
    int getCents() const { return m_cents; }
};

class Point {
private:
    int x;
    int y;
public:
    Point(int v1 = 0, int v2 = 0) : x(v1), y(v2) { std :: cout << "Constructor" << std :: endl; };
    Point(Point& a) : x(a.x), y(a.y) {std :: cout << "copy constructor" << std :: endl;};

    friend std::ostream& operator<<(std::ostream& out, const Point& p);
};

std::ostream& operator<<(std::ostream& out, const Point& p) {
        out << p.x << "," << p.y ;
        return out;
}

#endif /* __ADVANCED_ADVANCED_H_ */
