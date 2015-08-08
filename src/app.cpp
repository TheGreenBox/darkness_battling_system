/*
 * g++(clang++) -std=c++11
 *
 */
#include <getopt.h>

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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


struct TArgs {
    std::vector<std::string> Filenames;
    std::vector<std::string> PhraseOfPower;
    size_t TimeLimit = 0;
    size_t MemoryLimit = 0;
    size_t Cores = 1;
};

TArgs argparse(int argn, char** args) {
    static struct option long_options[] = {
        {"filename",        required_argument,  0,  'f' },
        {"time-limit",      required_argument,  0,  't' },
        {"memory-limit",    required_argument,  0,  'm' },
        {"cores",           required_argument,  0,  'c' },
        {"phrase",          required_argument,  0,  'p' },
        {"help",            no_argument,        0,  'h' },
        {0,                 0,                  0,   0 }
    };

    TArgs arguments;
    int option_index = 0;
    while (
        int c = getopt_long(argn, args, "f:t:m:c:p:h:?", long_options, &option_index)
    ) {
        if (c == -1) {
            break;
        } else if (c == 'f') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            arguments.Filenames.push_back(optarg);
        } else if (c == 't') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            arguments.TimeLimit = std::stoi(optarg);
        } else if (c == 'm') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            arguments.MemoryLimit = std::stoi(optarg);
        } else if (c == 'c') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            arguments.Cores = std::stoi(optarg);
        } else if (c == 'p') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            arguments.PhraseOfPower.push_back(optarg);
        } else if (c == 'h' || c == '?') {
            std::cerr << "Usage:\n"
                " -f  FILENAME    File containing JSON encoded input\n"
                " -t  NUMBER  Time limit, in seconds, to produce output\n"
                " -m  NUMBER  Memory limit, in megabytes, to produce output\n"
                " -c  NUMBER  Number of processor cores available\n"
                " -p  STRING  Phrase of power\n"
                " -h, -?, --help : Print this help\n"
            ;
            break;
        } else {
            if (0 != opterr) {
                throw ArgparseException();
            }
        }
    };
    return arguments;
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

