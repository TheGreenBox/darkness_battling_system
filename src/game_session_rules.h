#pragma once

#include "game_set_settings.h"
#include "board.h"

#include <lib/json/json/json-forwards.h>

#include <istream>

class TGameSessionRules {
public:
    explicit TGameSessionRules(std::istream& jsonIn);

    TGameSetSettings NextSet();

    TBoard GetInitialBoard() const;

private:
    TBoard InitialBoard;
    std::vector<TUnit> Units;
    size_t UnitsCount;

    using TSeed = long long int;
    std::vector<TSeed> Seeds;
};
