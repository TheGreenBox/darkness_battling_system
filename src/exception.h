#pragma once

#include <sstream>
#include <string>

class TException: public std::exception {
private:
    std::string whatHappen;

public:
    TException() {}
    TException(const std::string& what)
        : whatHappen(what) {
    }

    template<typename T>
    TException& operator<<(const T& val) {
        std::ostringstream ostr(whatHappen, std::ios_base::ate);
        ostr << val;
        whatHappen = ostr.str();
        return *this;
    }

    const char* what() const throw() override {
        return whatHappen.c_str();
    }
};

