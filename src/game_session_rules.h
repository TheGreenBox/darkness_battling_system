#pragma once

#include "game_set_settings.h"
#include "board.h"

#include <lib/json/json/json-forwards.h>

#include <deque>
#include <istream>
#include <random>

class TGameSessionRules {
public:
    explicit TGameSessionRules(std::istream& jsonIn);

    TGameSetSettings NextSet();

    TBoard GetInitialBoard() const;

private:
    TBoard InitialBoard;
    std::vector<TUnit> Units;
    size_t SourceLength;

    using TSeed = uint64_t;;
    std::deque<TSeed> Seeds;
};

namespace Private {

    class TSeriesGenerator {
    public:
        using Type = uint64_t;
        TSeriesGenerator(Type seed, Type range);

        size_t Next();

    private:
        static const Type Modulus    = Type(1) << 32;
        static const Type Multiplier = 1103515245;
        static const Type Increment  = 12345;

        std::linear_congruential_engine<
            Type,
            Multiplier,
            Increment,
            Modulus
        > Generator;
        Type Number;
        Type Range;

        static Type Get16to30bits(Type number);
    };
};

