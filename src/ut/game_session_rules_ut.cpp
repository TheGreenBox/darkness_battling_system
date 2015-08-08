#include "game_session_rules.h"
#include "exception.h"

#include <lib/json/json/json.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Test1() {
    std::string in =
        "{"
        "    \"filled\": ["
        "        {"
        "            \"x\": 1,"
        "            \"y\": 2"
        "        },{"
        "            \"x\": 2,"
        "            \"y\": 2"
        "        },{"
        "            \"x\": 9,"
        "            \"y\": 7"
        "        }"
        "    ],"
        "    \"height\": 8,"
        "    \"id\": 21,"
        "    \"sourceLength\": 20,"
        "    \"sourceSeeds\": [ 0 ],"
        "    \"units\": ["
        "        {"
        "            \"members\": ["
        "                {"
        "                    \"x\": 0,"
        "                    \"y\": 0"
        "                }"
        "            ],"
        "            \"pivot\": {"
        "                \"x\": 0,"
        "                \"y\": 0"
        "            }"
        "        }"
        "    ],"
        "    \"width\": 10"
        "}"
    ;
    std::istringstream inStream(in.c_str());
    TGameSessionRules gameSessionRules(inStream);
    auto board = gameSessionRules.GetInitialBoard();
    if (board.CellIsLocked(5, 5)) {
        throw TException("unit test error") << __FILE__ << ":" << __LINE__;
    }
    if (!board.CellIsLocked(1, 2)) {
        throw TException("unit test error") << __FILE__ << ":" << __LINE__;
    }
}

void TestSeriesGenerator() {
    std::vector<size_t> rightAnswer{0, 59, 19, 101, 75, 126, 64, 43, 26, 85,};
    Private::TSeriesGenerator gen(17, 167);

    for (const auto& right : rightAnswer) {
        size_t generated = gen.Next();
        if (right != generated) {
            throw TException("unit test error")
                << " " << __FILE__ << ":" << __LINE__
                << " " << "TSeriesGenerator error"
                << " wrong answer: " << generated
                << " expected: " << right
            ;
        }
    }
};

int main() {
    Test1();
    TestSeriesGenerator();
    return 0;
}
