#include "coordinate_systems.h"

#include "exception.h"

#include <cmath>

namespace Coords {

ColRowPoint::ColRowPoint(Coordinate column, Coordinate row)
    : Column(column)
    , Row(row) {}

bool ColRowPoint::operator==(const ColRowPoint& other) const {
    return Column == other.Column && Row == other.Row;
}

bool ColRowPoint::operator!=(const ColRowPoint& other) const {
    return !operator==(other);
}

StraightColRowPoint::StraightColRowPoint(Coordinate column, Coordinate row)
    : Column(column)
    , Row(row) {}

bool StraightColRowPoint::operator==(const StraightColRowPoint& other) const {
    return Column == other.Column && Row == other.Row;
}

bool StraightColRowPoint::operator!=(const StraightColRowPoint& other) const {
    return !operator==(other);
}

StraightColRowPoint Straighten(const ColRowPoint& colRow) {
    StraightColRowPoint::Coordinate column
        = colRow.Column - std::floor(static_cast<float>(colRow.Row) / 2);
    StraightColRowPoint::Coordinate row = colRow.Row;

    return StraightColRowPoint(column, row);
}

ColRowPoint Unstraighten(const StraightColRowPoint& straight) {
    ColRowPoint::Coordinate row = straight.Row;
    ColRowPoint::Coordinate column
        = straight.Column + std::floor(static_cast<float>(straight.Row) / 2);;

    return ColRowPoint(column, row);
}


HexPoint::HexPoint(Coordinate x, Coordinate y, Coordinate z)
    : X(x)
    , Y(y)
    , Z(z) {
    if (X + Y + Z != 0) {
        throw TException("Invalid hex point created at ")
            << __FILE__ << ":" << __LINE__;
    }
}

bool HexPoint::operator==(const HexPoint& other) const {
    return X == other.X && Y == other.Y && Z == other.Z;
}

bool HexPoint::operator!=(const HexPoint& other) const {
    return !operator==(other);
}

HexPoint ToHex(const StraightColRowPoint& point) {
    HexPoint::Coordinate x = point.Column;
    HexPoint::Coordinate y = point.Row;
    HexPoint::Coordinate z = - x - y;

    return HexPoint(x, y, z);
}

HexPoint ToHex(const ColRowPoint& point) {
    return ToHex(Straighten(point));
}

template <>
StraightColRowPoint FromHex<StraightColRowPoint>(const HexPoint& hex) {
    return StraightColRowPoint(hex.X, hex.Y);
}

template <>
ColRowPoint FromHex<ColRowPoint>(const HexPoint& hex) {
    auto straigthPoint = FromHex<StraightColRowPoint>(hex);
    return Unstraighten(straigthPoint);
}

} // namespace Coords
