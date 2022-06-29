#include <functional>
#include<iostream>
#include <ostream>
#include "advanced.h"

using std::cout;
using std::endl;

int ret5() {
    return 5;
}

bool EqualInARange(int x, int y) {
    return abs(x - y) < 3;
}

bool isEqual(int x, int y, std::function<bool(int, int)> cmp) {
    return cmp(x, y);
}