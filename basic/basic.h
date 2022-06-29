#ifndef __BASIC_BASIC_H_
#define __BASIC_BASIC_H_
void hello();
int add(int x, int y);
void addToZ(int& x, int& y, int& z);
void defineTrigger();
void printInt(int x);

namespace testns1 {
    int doSomethingInNS(int x, int y);
} // namespace testns1

namespace testns2 {
    int doSomethingInNS(int x, int y);
}

const int y = 5;
namespace constants
{
    // constants have internal linkage by default
    inline constexpr double pi { 3.1415926 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}

template <typename T, typename U>
T mymax(T x, U y) {
    return x > y ? x : y;
};

#endif /* __BASIC_BASIC_H_ */
