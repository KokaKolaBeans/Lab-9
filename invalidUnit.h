// invalidUnit.h
#ifndef INVALIDUNIT_H
#define INVALIDUNIT_H

#include <string>

class invalidUnit
{
private:
    std::string message;

public:
    invalidUnit(std::string msg) : message(msg) {}

    std::string what() { return message; }
};

#endif
