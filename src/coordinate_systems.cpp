#include "coordinate_systems.h"

#include <cmath>

namespace Coords {

RowColPoint::RowColPoint(Coordinate column, Coordinate row)
    : Column(column)
    , Row(row) {}

bool RowColPoint::operator==(const RowColPoint& other) const {
    return Column == other.Column && Row == other.Row;
}

bool RowColPoint::operator!=(const RowColPoint& other) const {
    return !operator==(other);
}

StraightRowColPoint::StraightRowColPoint(Coordinate column, Coordinate row)
    : Column(column)
    , Row(row) {}

bool StraightRowColPoint::operator==(const StraightRowColPoint& other) const {
    return Column == other.Column && Row == other.Row;
}

bool StraightRowColPoint::operator!=(const StraightRowColPoint& other) const {
    return !operator==(other);
}

StraightRowColPoint Straighten(const RowColPoint& rowCol) {
    StraightRowColPoint::Coordinate column
        = rowCol.Column - std::floor(static_cast<float>(rowCol.Row) / 2);
    StraightRowColPoint::Coordinate row = rowCol.Row;

    return StraightRowColPoint(column, row);
}

RowColPoint Unstraighten(const StraightRowColPoint& straight) {
    RowColPoint::Coordinate row = straight.Row;
    RowColPoint::Coordinate column
        = straight.Column + std::floor(static_cast<float>(straight.Row) / 2);;

    return RowColPoint(column, row);
}


HexPoint::HexPoint(Coordinate x, Coordinate y, Coordinate z)
    : X(x)
    , Y(y)
    , Z(z) {}

bool HexPoint::operator==(const HexPoint& other) const {
    return X == other.X && Y == other.Y && Z == other.Z;
}

bool HexPoint::operator!=(const HexPoint& other) const {
    return !operator==(other);
}

HexPoint ToHex(const StraightRowColPoint& point) {
    HexPoint::Coordinate x = point.Column;
    HexPoint::Coordinate y = point.Row;
    HexPoint::Coordinate z = - x - y;

    return HexPoint(x, y, z);
}

HexPoint ToHex(const RowColPoint& point) {
    return ToHex(Straighten(point));
}

template <>
StraightRowColPoint FromHex<StraightRowColPoint>(const HexPoint& hex) {
    return StraightRowColPoint(hex.X, hex.Y);
}

template <>
RowColPoint FromHex<RowColPoint>(const HexPoint& hex) {
    auto straigthPoint = FromHex<StraightRowColPoint>(hex);
    return Unstraighten(straigthPoint);
}

} // namespace Coords
