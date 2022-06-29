#ifndef __RAII_TESTCLASSES_H_
#define __RAII_TESTCLASSES_H_
#include <iostream>
#include <string>
#include <utility>
class Cat {
private:
    std::string _name;

public:
    Cat(std::string name) :
        _name(std::move(name)){};
    void getName() const {
        std::cout << _name << std::endl;
    }
};

void testConstRef();

#endif /* __RAII_TESTCLASSES_H_ */
