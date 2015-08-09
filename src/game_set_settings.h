#pragma once

#include <vector>

#include "unit.h"
#include "types.h"

class TGameSetSettings {
public:
    explicit TGameSetSettings() {}

    using TUnitOrder = std::vector<TUnit>;
    using TIterator = TUnitOrder::iterator;
    using TConstIterator = TUnitOrder::const_iterator;

    void AssignSeed(TSeed);
    TSeed GetSeed() const;

    TIterator begin();
    TConstIterator begin() const;

    TIterator end();
    TConstIterator end() const;

    void Push(TUnit&&);

private:
    TUnitOrder Units;
    TSeed Seed;

    // TODO: Are you sure ?
    // std::string PhrasesOfPower;
};

