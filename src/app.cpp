/*
 * g++(clang++) -std=c++11
 *
 */
#include "exception.h"
#include "game_session_rules.h"
#include "output_format.h"
#include "solution_cmd.h"
#include "way_graph.h"

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

        std::vector<TProblemSolution> solutions;
        for (const auto& fname : arguments.Filenames) {
            std::fstream fin(fname);
            TGameSessionRules session(fin);
            while (!session.Empty()) {
                auto gameSet = session.NextSet();

                solutions.emplace_back();
                TProblemSolution& solution = solutions.back();
                solution.ProblemId = session.GetProblemId();
                solution.Seed = gameSet.GetSeed();

                TBoard board = session.GetInitialBoard();
                size_t unitNum = 0;
                for (const auto& unit : gameSet) {
                    unit.DebugPrint();
                    std::cerr << board.ToString() << std::endl;
                    TUnit startPos = board.TeleportUnitToSpawnPosition(unit);
                    std::cerr << "Start pos: ";
                    startPos.DebugPrint();
                    TWayGraph wayGraph(2, 2);
                    wayGraph.Build(board, startPos);
                    std::cerr << wayGraph.ToString() << std::endl;

                    size_t startRotation = 0;
                    auto endPositionQueue = wayGraph.FindPositionWithMaxMetrics(unit, startRotation);
                    std::cerr << "Position queue size: " << endPositionQueue.size() << std::endl;

                    TUnit endUnit = unit.Clone();
                    TWayGraph::TWays ways;
                    while (ways.empty() && !endPositionQueue.empty()) {
                        const auto& endPos = endPositionQueue.top();
                        endUnit = endPos.Unit.Clone();
                        std::cerr << "End pos: ";
                        endUnit.DebugPrint();
                        ways = wayGraph.FindWay(
                            startPos.GetPivot().GetPosition(),
                            0,
                            endPos.Unit.GetPivot().GetPosition(),
                            endPos.Direction
                        );
                        endPositionQueue.pop();
                    }

                    std::cerr << "ways size: " << ways.size() << '\n' << std::endl;
                    if (ways.empty()) {
                        break;
                    }

                   // solution.Solution += "$";
                   // solution.Solution += std::to_string(unitNum);
                   // solution.Solution += "$";
                    ++unitNum;
                    solution.Solution += MakeSolutionCmdFrom(ways.front());

                    std::cerr << "End pos: ";
                    endUnit.DebugPrint();

                    board.LockCells(endUnit);
                    board.CollapseRows();
                }
            }
        }
        AnswerFormattedPrint(solutions, std::cout);

    } catch (const std::exception& except) {
        std::cerr << except.what() << std::endl;
        return 1;
    }
    return 0;
}

