#include <iostream>
#include <sstream>
#include <string>

#include "segment.h"
#include "unit.h"

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

std::string GenerateComment(const TSegment& result, const TSegment& expected) {
    std::stringstream builder;
    const auto& expectedPos = expected.GetPosition();
    const auto& resultPos = result.GetPosition();
    builder << "Expected 2D (" << expectedPos.Column << ", "
        << expectedPos.Row << "), got ("
        << resultPos.Column << ", "
        << resultPos.Row << ")";

    return std::string(builder.str());
}

namespace Rotation {

void TestAroundSelf() {
    TSegment segment(Coords::TColRowPoint(1, 3));

    TSegment result = segment.RotateAround(
        segment.GetPosition(),
        EMoveOperations::ROTATE_CLOCKWISE
    );

    TSegment expected = segment;

    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test1() {
    TSegment pivot(Coords::TColRowPoint(0, 0));
    TSegment segment(Coords::TColRowPoint(0, 1));

    TSegment result = segment.RotateAround(
        pivot.GetPosition(),
        EMoveOperations::ROTATE_ANTI_CLOCKWISE
    );

    TSegment expected = TSegment(Coords::TColRowPoint(1, 0));

    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test2() {
    TSegment pivot(Coords::TColRowPoint(1, 1));
    TSegment segment(Coords::TColRowPoint(3, 2));

    TSegment result = segment.RotateAround(
        pivot.GetPosition(),
        EMoveOperations::ROTATE_ANTI_CLOCKWISE
    );

    TSegment expected = TSegment(Coords::TColRowPoint(3, 0));

    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test3() {
    TSegment pivot(Coords::TColRowPoint(3, 3));
    TSegment segment(Coords::TColRowPoint(2, 0));

    TSegment result = segment.RotateAround(
        pivot.GetPosition(),
        EMoveOperations::ROTATE_CLOCKWISE
    );

    TSegment expected = TSegment(Coords::TColRowPoint(5, 0));

    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test4() {
    TSegment pivot(Coords::TColRowPoint(1, 3));
    TSegment segment(Coords::TColRowPoint(1, 0));

    TSegment result = segment.RotateAround(
        pivot.GetPosition(),
        EMoveOperations::ROTATE_ANTI_CLOCKWISE
    );

    TSegment expected = TSegment(Coords::TColRowPoint(-1, 2));

    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void TestReversability() {
    for (Coords::TColRowPoint::TCoordinate col = -10; col < 10; ++col) {
        for (Coords::TColRowPoint::TCoordinate row = -10; row < 10; ++row) {
            TSegment pivot(Coords::TColRowPoint(col, row));
            TSegment origin(Coords::TColRowPoint(2 * col, 2 * row));

            TSegment rotated = origin.RotateAround(
                pivot.GetPosition(),
                EMoveOperations::ROTATE_CLOCKWISE
            );

            TSegment rotatedBack = rotated.RotateAround(
                pivot.GetPosition(),
                EMoveOperations::ROTATE_ANTI_CLOCKWISE
            );


            ExpectEqual(origin, rotatedBack);
        }
    }
}

} // namespace Rotation

namespace Slide {

void Test1() {
    TSegment segment(Coords::TColRowPoint(1, 0));
    TSegment result = segment.Slide(EMoveOperations::SLIDE_EAST);

    TSegment expected = TSegment(Coords::TColRowPoint(2, 0));
    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test2() {
    TSegment segment(Coords::TColRowPoint(1, 0));
    TSegment result = segment.Slide(EMoveOperations::SLIDE_WEST);

    TSegment expected = TSegment(Coords::TColRowPoint(0, 0));
    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test3() {
    TSegment segment(Coords::TColRowPoint(1, 0));
    TSegment result = segment.Slide(EMoveOperations::SLIDE_SOUTHEAST);

    TSegment expected = TSegment(Coords::TColRowPoint(1, 1));
    ExpectEqual(result, expected, GenerateComment(result, expected));
}

void Test4() {
    TSegment segment(Coords::TColRowPoint(1, 0));
    TSegment result = segment.Slide(EMoveOperations::SLIDE_SOUTHWEST);

    TSegment expected = TSegment(Coords::TColRowPoint(0, 1));
    ExpectEqual(result, expected, GenerateComment(result, expected));
}

} // namespace Slide

namespace Teleport {

void TestToSelf() {
    TSegment pivot(Coords::TColRowPoint(1, 1));
    TUnit::TSegments unitSegments = {TSegment(Coords::TColRowPoint(1, 1))};
    TUnit unit(pivot, std::move(unitSegments));

    TUnit result = unit.TeleportTo(pivot.GetPosition());

    TUnit expected = unit.Clone();
    ExpectEqual(result, expected);
}

void TestToOther() {
    TUnit::TSegments unitSegments = {TSegment(Coords::TColRowPoint(2, 1))};
    TSegment pivot(Coords::TColRowPoint(1, 1));
    TUnit unit(pivot, std::move(unitSegments));
    TSegment to(Coords::TColRowPoint(5, 3));

    TUnit result = unit.TeleportTo(to.GetPosition());

    TUnit::TSegments expectedSegments = {TSegment(Coords::TColRowPoint(6, 3))};
    TUnit expected(to, std::move(expectedSegments));
    ExpectEqual(result, expected);
}

} // namespace Teleport

} // unnamed namespace

int main() {
    Rotation::TestAroundSelf();
    Rotation::Test1();
    Rotation::Test2();
    Rotation::Test3();
    Rotation::Test4();
    Rotation::TestReversability();

    Slide::Test1();
    Slide::Test2();
    Slide::Test3();
    Slide::Test4();

    Teleport::TestToSelf();
    Teleport::TestToOther();

    return 0;
}