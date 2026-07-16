// invalidRange.h
#ifndef INVALIDRANGE_H
#define INVALIDRANGE_H
#include <string>

class invalidRange
{
private:
    std::string message;

public:
    invalidRange(std::string msg) : message(msg) {}

    std::string what() { return message; }
};

#endif
