#include "coordinate_systems.h"

#include <iostream>
#include <sstream>
#include <vector>

namespace {

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

void TestReversability() {
    for (Coords::TColRowPoint::TCoordinate col = -10; col < 10; ++col) {
        for (Coords::TColRowPoint::TCoordinate row = -10; row < 10; ++row) {
            Coords::TColRowPoint point(col, row);
            Coords::THexPoint hex = Coords::ToHex(point);
            if (Coords::FromHex(hex) != point) {
                std::cout << "Hex reversability test failed on "
                          << "column " << col << " : row " << row << std::endl;
                return;
            }
        }
    }
}

void Test1() {
    std::vector<Coords::TColRowPoint> colRows;
    std::vector<Coords::THexPoint> hexes;

    colRows.emplace_back(0, 0);
    hexes.emplace_back(0, 0, 0);

    colRows.emplace_back(0, 1);
    hexes.emplace_back(0, 1, -1);

    colRows.emplace_back(1, 0);
    hexes.emplace_back(1, 0, -1);

    colRows.emplace_back(2, 0);
    hexes.emplace_back(2, 0, -2);

    colRows.emplace_back(-2, 2);
    hexes.emplace_back(-3, 2, 1);

    ExpectEqual(colRows.size(), hexes.size(), "Test vectors size mismatch");

    for (size_t index = 0; index < colRows.size(); ++index) {
        std::stringstream commentBuilder;
        const auto& colRow = colRows.at(index);
        commentBuilder << "2D->Hex->2D test: 2D (" << colRow.Column << ", "
            << colRow.Row << ")";

        ExpectEqual(Coords::ToHex(colRows.at(index)), hexes.at(index), commentBuilder.str());
        ExpectEqual(colRows.at(index), Coords::FromHex(hexes.at(index)), commentBuilder.str());
    }
}

} // unnamed namespace

int main() {
    TestReversability();
    Test1();
    return 0;
}
