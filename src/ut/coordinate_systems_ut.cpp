#include "coordinate_systems.h"

#include <iostream>
#include <vector>

namespace {

namespace TwoD {

bool AreEqual(
    const Coords::RowColPoint& rowCol,
    const Coords::StraightRowColPoint& straight
) {
    return rowCol.Row == straight.Row && rowCol.Column == straight.Column;
}

bool AreUnequal(
    const Coords::RowColPoint& rowCol,
    const Coords::StraightRowColPoint& straight
) {
    return !AreEqual(rowCol, straight);
}


void TestReversability() {
    for (Coords::RowColPoint::Coordinate col = 0; col < 10; ++col) {
        for (Coords::RowColPoint::Coordinate row = 0; row < 10; ++row) {
            Coords::RowColPoint point(col, row);
            Coords::StraightRowColPoint straight = Coords::Straighten(point);
            if (Coords::Unstraighten(straight) != point) {
                std::cout << "Reversability test failed on "
                          << "column " << col << " : row " << row << std::endl;
                return;
            }
        }
    }
}

void TestZeroPointUnmovability() {
    Coords::RowColPoint zero(0, 0);
    Coords::StraightRowColPoint straightZero = Coords::Straighten(zero);

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
    std::vector<Coords::RowColPoint> rowCols;
    std::vector<Coords::StraightRowColPoint> straights;


    rowCols.emplace_back(   0, 1);
    straights.emplace_back( 0, 1);
    rowCols.emplace_back(  -1, 0);
    straights.emplace_back(-1, 0);
    rowCols.emplace_back(   5000, 0);
    straights.emplace_back( 5000, 0);

    rowCols.emplace_back(   0, 2);
    straights.emplace_back(-1, 2);

    rowCols.emplace_back(  1, 2);
    straights.emplace_back(0, 2);

    rowCols.emplace_back(  3, 3);
    straights.emplace_back(2, 3);

    ExpectEqual(rowCols.size(), straights.size(), "Test vectors size mismatch");

    for (size_t index = 0; index < rowCols.size(); ++index) {
        ExpectEqual(Coords::Straighten(rowCols.at(index)), straights.at(index));
        ExpectEqual(rowCols.at(index), Coords::Unstraighten(straights.at(index)));
    }
}

} // namespace TwoD

namespace ThreeD {

}

} // unnamed namespace

int main() {
    TwoD::TestZeroPointUnmovability();
    TwoD::TestReversability();
    TwoD::Test1();
    return 0;
}
