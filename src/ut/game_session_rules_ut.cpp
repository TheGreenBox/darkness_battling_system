#include "game_session_rules.h"
#include "exception.h"

#include <lib/json/json/json.h>

#include <sstream>
#include <string>
#include <iostream>

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

int main() {
    Test1();
    return 0;
}
