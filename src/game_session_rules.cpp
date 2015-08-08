#include "game_session_rules.h"

#include <lib/json/json/json.h>

#include <cstdint>

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

    SourceLength = root.get("sourceLength", "").asUInt64();

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
    Private::TSeriesGenerator gen(Seeds.front(), Units.size());
    Seeds.pop_front();
    TGameSetSettings gameSet;
    for (size_t i = 0; i < SourceLength; ++i) {
        gameSet.Push(
            Units[gen.Next()].Clone()
        );
    }
    return gameSet;
}

TBoard TGameSessionRules::GetInitialBoard() const {
    return InitialBoard;
}

namespace Private {
    TSeriesGenerator::TSeriesGenerator(Type seed, Type range)
        : Generator(seed)
        , Number(seed)
        , Range(range)
    {
    }
    size_t TSeriesGenerator::Next() {
        size_t ret = static_cast<size_t>(Get16to30bits(Number) % Range);
        Number = Generator();
        return ret;
    }

    TSeriesGenerator::Type TSeriesGenerator::Get16to30bits(Type number) {
        number &= ~(Type(-1) << 31);
        number >>= 16;
        return number;
    }
};  // Private
