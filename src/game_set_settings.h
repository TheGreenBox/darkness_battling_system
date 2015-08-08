#pragma once

class TGameSetSettings {
public:
    explicit TGameSetSettings() {}

    using TUnitOrder = std::vector<TUnit>;
    using TIterator = TUnitOrder::iterator;

    TIterator begin();
    TIterator begin() const;

    TIterator end();
    TIterator end() const;

    void Push(const TUnit&);

    TUnit Pop();

private:
    TUnitOrder Units;

    // TODO: Are you sure ?
    // std::string PhrasesOfPower;
};

