/*
 * g++(clang++) -std=c++11
 *
 */
#include "exception.h"
#include "game_session_rules.h"
#include "output_format.h"

#include <lib/json/json/json.h>

#include <getopt.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

struct TArgs {
    std::vector<std::string> Filenames;
    std::vector<size_t> ProblemIds;
    std::vector<std::string> PhraseOfPower;
    std::string DebugCmd;
    size_t TimeLimit = 0;
    size_t MemoryLimit = 0;
    size_t Cores = 1;
};

TArgs argparse(int argn, char** args) {
    static struct option long_options[] = {
        {"filename",        required_argument,  0,  'f' },
        {"problems-ids",    required_argument,  0,  'i' },
        {"time-limit",      required_argument,  0,  't' },
        {"memory-limit",    required_argument,  0,  'm' },
        {"cores",           required_argument,  0,  'c' },
        {"phrase",          required_argument,  0,  'p' },
        {"debug",           required_argument,  0,  'd' },
        {"help",            no_argument,        0,  'h' },
        {0,                 0,                  0,   0 }
    };

    TArgs arguments;
    int option_index = 0;
    while (
        int c = getopt_long(argn, args, "f:i:t:m:c:p:h:d:?", long_options, &option_index)
    ) {
        if (c == -1) {
            break;
        } else if (c == 'f') {
            arguments.Filenames.push_back(optarg);
        } else if (c == 't') {
            arguments.TimeLimit = std::stoi(optarg);
        } else if (c == 'm') {
            arguments.MemoryLimit = std::stoi(optarg);
        } else if (c == 'c') {
            arguments.Cores = std::stoi(optarg);
        } else if (c == 'p') {
            arguments.PhraseOfPower.push_back(optarg);
        } else if (c == 'd') {
            arguments.DebugCmd = optarg;
        } else if (c == 'h' || c == '?') {
            std::cerr << "Usage:\n"
                " -f  FILENAME  File containing JSON encoded input\n"
                " -i  ID        The 'id' of the game configuration\n"
                " -t  NUMBER    Time limit, in seconds, to produce output\n"
                " -m  NUMBER    Memory limit, in megabytes, to produce output\n"
                " -c  NUMBER    Number of processor cores available\n"
                " -p  STRING    Phrase of power\n"
                " -d  STRING    Debug mode\n"
                " -h, -?, --help : Print this help\n"
            ;
            break;
        } else {
            if (0 != opterr) {
                throw TException("Invalid configurating for argparse:")
                    << " unknown option: -" << char(c);
            }
        }
    };
    return arguments;
}

int main(int argn, char** args) {
    try {
        TArgs arguments = argparse(argn, args);

        for (const auto& fname : arguments.Filenames) {
            std::fstream fin(fname);
            TGameSessionRules session(fin);
            if (arguments.DebugCmd == "src") {
                auto gameSet = session.NextSet();
                for (const auto& u : gameSet) {
                    Json::Value jsonRec(Json::objectValue);
                    jsonRec["members"] = Json::arrayValue;
                    for (const auto& seg : u.GetSegments()) {
                        Json::Value jsonMemmber(Json::objectValue);
                        const auto& position = seg.GetPosition();
                        jsonMemmber["c"] = position.Column;
                        jsonMemmber["r"] = position.Row;
                        jsonRec["members"].append(jsonMemmber);
                    }
                    Json::Value jsonPivot(Json::objectValue);
                    const auto& pivotPosisiton = u.GetPivot().GetPosition();
                    jsonPivot["c"] = pivotPosisiton.Column;
                    jsonPivot["r"] = pivotPosisiton.Row;
                    jsonRec["pivot"] = jsonPivot;

                    Json::StreamWriterBuilder builder;
                    builder["indentation"] = "";  // or whatever you like
                    std::unique_ptr<Json::StreamWriter> writer(
                        builder.newStreamWriter());
                    writer->write(jsonRec, &std::cout);
                    std::cout << std::endl;  // add lf and flush
                }
            }
        }

    } catch (const std::exception& except) {
        std::cerr << except.what() << std::endl;
        return 1;
    }
    return 0;
}

