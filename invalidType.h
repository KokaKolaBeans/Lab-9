// invalidType.h
#ifndef INVALIDTYPE_H
#define INVALIDTYPE_H

#include <string>

class invalidType
{
private:
    std::string message;

public:
    invalidType(std::string msg) : message(msg) {}

    std::string what() { return message; }
};

#endif
