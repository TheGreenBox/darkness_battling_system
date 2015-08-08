/*
 * g++(clang++) -std=c++11
 *
 */
#include <getopt.h>

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

class ArgparseException: public std::exception {
public:
    ArgparseException() {}
    ArgparseException(const std::string& what) {
        whatHappen.append(what);
    }

    template<typename T>
    ArgparseException& operator<<(const T& val) {
        std::ostringstream ostr;
        ostr << val;
        whatHappen.append(ostr.str());
        return *this;
    }

    const char* what() const throw() override {
        return whatHappen.c_str();
    }

private:
    std::string whatHappen = "[argument parser exception] ";
};

void argparse(int argn, char** args) {
    static struct option long_options[] = {
        {"input",       required_argument,  0,  'i' },
        {"output",      required_argument,  0,  'o' },
        {"help",        no_argument,        0,  'h' },
        {0,             0,                  0,   0 }
    };

    std::string input;
    std::string output;

    int option_index = 0;
    while (
        int c = getopt_long(argn, args, "i:o:?:h", long_options, &option_index)
    ) {
        if (c == -1) {
            break;
        } else if (c == 'i') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'i\'");
            }
            input = optarg;
        } else if (c == 'o') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            output = optarg;
        } else if (c == 'h' || c == '?') {
            std::cerr << "Usage:\n"
                << " -i, --input : Input file\n"
                << " -o, --output : Output file\n"
                << " -h, -?, --help : Print this help\n"
            ;
            return;
        } else {
            if (0 != opterr) {
                throw ArgparseException();
            }
        }
    };
}

int main(int argn, char** args) {
    try {
        argparse(argn, args);
    } catch (const std::exception& except) {
        std::cerr << except.what() << std::endl;
        return 1;
    }
    return 0;
}

