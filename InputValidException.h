#ifndef _INPUT_VALID_EXCEPTION_H
#define _INPUT_VALID_EXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InputValidException : public std::exception
{
public:
    InputValidException(const std::string& msg = "") : std::exception(msg.c_str()) {}
};

#endif