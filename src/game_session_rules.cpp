#include "game_session_rules.h"

#include <lib/json/json/json.h>

TGameSessionRules::TGameSessionRules(std::istream& jsonIn)
    : InitialBoard(0, 0)
{
    Json::Value root;
    jsonIn >> root;

    std::string my_encoding = root.get("my-encoding", "UTF-32" ).asString();
    InitialBoard = TBoard(
        root.get("width", "").asUInt64(),
        root.get("height", "").asUInt64()
    );

    for (const auto& unit : root.get("filled", "")) {
        InitialBoard.LockCell(
            unit.get("x", "").asInt64(),
            unit.get("y", "").asInt64()
        );
    }

    UnitsCount = root.get("sourceLength", "").asUInt64();

    for (const auto& seed : root.get("sourceSeeds", "")) {
        Seeds.push_back(seed.asLargestInt());
    }

    for (const auto& unit : root.get("units", "")) {
        TUnit::TSegments members;
        for (const auto& member : unit.get("members", "")) {
            members.push_back(
                TSegment(
                    member.get("x", "").asInt64(),
                    member.get("y", "").asInt64()
                )
            );
        }
        auto pivot = unit.get("pivot", "");
        Units.push_back(
            TUnit(
                TSegment(
                    pivot.get("x", "").asInt64(),
                    pivot.get("y", "").asInt64()
                ),
                std::move(members)
            )
        );
    }
}

TGameSetSettings TGameSessionRules::NextSet() {
    return TGameSetSettings();
}

TBoard TGameSessionRules::GetInitialBoard() const {
    return InitialBoard;
}

