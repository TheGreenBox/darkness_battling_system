#include "coordinate_systems.h"

#include <iostream>
#include <vector>

namespace {

namespace TwoD {

bool AreEqual(
    const Coords::ColRowPoint& colRow,
    const Coords::StraightColRowPoint& straight
) {
    return colRow.Row == straight.Row && colRow.Column == straight.Column;
}

bool AreUnequal(
    const Coords::ColRowPoint& colRow,
    const Coords::StraightColRowPoint& straight
) {
    return !AreEqual(colRow, straight);
}


void TestReversability() {
    for (Coords::ColRowPoint::Coordinate col = -10; col < 10; ++col) {
        for (Coords::ColRowPoint::Coordinate row = -10; row < 10; ++row) {
            Coords::ColRowPoint point(col, row);
            Coords::StraightColRowPoint straight = Coords::Straighten(point);
            if (Coords::Unstraighten(straight) != point) {
                std::cout << "Reversability test failed on "
                          << "column " << col << " : row " << row << std::endl;
                return;
            }
        }
    }
}

void TestZeroPointUnmovability() {
    Coords::ColRowPoint zero(0, 0);
    Coords::StraightColRowPoint straightZero = Coords::Straighten(zero);

    if (AreUnequal(zero, straightZero)) {
        std::cout << "Zero test failed" << std::endl;
    }
}

template<typename T> void ExpectEqual(
    const T& lhs,
    const T& rhs,
    std::string comment = std::string()
) {
    if (lhs != rhs) {
        std::cout << "Equality test failed";

        if (!comment.empty()) {
            std::cout << " with comment: '" << comment << "'";
        }

        std::cout << std::endl;
    }
}

void Test1() {
    std::vector<Coords::ColRowPoint> colRows;
    std::vector<Coords::StraightColRowPoint> straights;


    colRows.emplace_back(   0, 1);
    straights.emplace_back( 0, 1);
    colRows.emplace_back(  -1, 0);
    straights.emplace_back(-1, 0);
    colRows.emplace_back(   5000, 0);
    straights.emplace_back( 5000, 0);

    colRows.emplace_back(   0, 2);
    straights.emplace_back(-1, 2);

    colRows.emplace_back(  1, 2);
    straights.emplace_back(0, 2);

    colRows.emplace_back(  3, 3);
    straights.emplace_back(2, 3);

    ExpectEqual(colRows.size(), straights.size(), "Test vectors size mismatch");

    for (size_t index = 0; index < colRows.size(); ++index) {
        ExpectEqual(Coords::Straighten(colRows.at(index)), straights.at(index));
        ExpectEqual(colRows.at(index), Coords::Unstraighten(straights.at(index)));
    }
}

} // namespace TwoD

namespace Hex {

void TestReversability() {
    for (Coords::StraightColRowPoint::Coordinate col = -10; col < 10; ++col) {
        for (Coords::StraightColRowPoint::Coordinate row = -10; row < 10; ++row) {
            Coords::StraightColRowPoint point(col, row);
            Coords::HexPoint hex = Coords::ToHex(point);
            if (Coords::FromHex<Coords::StraightColRowPoint>(hex) != point) {
                std::cout << "Hex reversability test failed on "
                          << "column " << col << " : row " << row << std::endl;
                return;
            }
        }
    }
}

void Test1() {
    std::vector<Coords::StraightColRowPoint> straights;
    std::vector<Coords::HexPoint> hexes;

    straights.emplace_back(0, 0);
    hexes.emplace_back(0, 0, 0);

    straights.emplace_back(0, 1);
    hexes.emplace_back(0, 1, -1);

    straights.emplace_back(1, 0);
    hexes.emplace_back(1, 0, -1);

    straights.emplace_back(2, 0);
    hexes.emplace_back(2, 0, -2);

    straights.emplace_back(-2, 2);
    hexes.emplace_back(-2, 1, 1);
}

} // namespace Hex

} // unnamed namespace

int main() {
    TwoD::TestZeroPointUnmovability();
    TwoD::TestReversability();
    TwoD::Test1();

    Hex::TestReversability();
    Hex::Test1();
    return 0;
}
