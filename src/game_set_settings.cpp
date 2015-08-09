#include "game_set_settings.h"

TGameSetSettings::TIterator TGameSetSettings::begin() {
    return Units.begin();
}

TGameSetSettings::TConstIterator TGameSetSettings::begin() const {
    return Units.begin();
}

TGameSetSettings::TIterator TGameSetSettings::end() {
    return Units.end();
}

TGameSetSettings::TConstIterator TGameSetSettings::end() const {
    return Units.end();
}

void TGameSetSettings::Push(TUnit&& unit) {
    Units.push_back(std::move(unit));
}

void TGameSetSettings::AssignSeed(TSeed seed) {
    Seed = seed;
}
TSeed TGameSetSettings::GetSeed() const {
    return Seed;
}
