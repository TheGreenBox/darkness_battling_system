#pragma once

#include <vector>

#include "unit.h"

class TGameSetSettings {
public:
    explicit TGameSetSettings() {}

    using TUnitOrder = std::vector<TUnit>;
    using TIterator = TUnitOrder::iterator;
    using TConstIterator = TUnitOrder::const_iterator;

    TIterator begin();
    TConstIterator begin() const;

    TIterator end();
    TConstIterator end() const;

    void Push(TUnit&&);

private:
    TUnitOrder Units;

    // TODO: Are you sure ?
    // std::string PhrasesOfPower;
};

