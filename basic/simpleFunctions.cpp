#include <iostream>

#include "basic.h"

#define TRIGGER

int add(int x, int y) {
    return x + y;
}

void addToZ(int &x, int &y, int &z) {
    z = x + y;
}

void defineTrigger() {
#ifdef TRIGGER
    std ::cout << "PULL THE TRIGGER!" << std ::endl;
#endif
}

void printInt(int x) {
    std::cout << x << std::endl;
}

namespace testns1 {
    int doSomethingInNS(int x, int y) {
        return x + y;
    }
} // namespace testns1

namespace testns2 {
    int doSomethingInNS(int x, int y) {
        return x - y;
    }
}

