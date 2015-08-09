#include "coordinate_systems.h"

#include "exception.h"

#include <cmath>

namespace Coords {

TColRowPoint::TColRowPoint(TCoordinate column, TCoordinate row)
    : Column(column)
    , Row(row) {}

bool TColRowPoint::operator==(const TColRowPoint& other) const {
    return Column == other.Column && Row == other.Row;
}

bool TColRowPoint::operator!=(const TColRowPoint& other) const {
    return !operator==(other);
}

TStraightColRowPoint::TStraightColRowPoint(TCoordinate column, TCoordinate row)
    : Column(column)
    , Row(row) {}

bool TStraightColRowPoint::operator==(const TStraightColRowPoint& other) const {
    return Column == other.Column && Row == other.Row;
}

bool TStraightColRowPoint::operator!=(const TStraightColRowPoint& other) const {
    return !operator==(other);
}

TStraightColRowPoint Straighten(const TColRowPoint& colRow) {
    TStraightColRowPoint::TCoordinate column
        = colRow.Column - std::floor(static_cast<float>(colRow.Row) / 2);
    TStraightColRowPoint::TCoordinate row = colRow.Row;

    return TStraightColRowPoint(column, row);
}

TColRowPoint Unstraighten(const TStraightColRowPoint& straight) {
    TColRowPoint::TCoordinate row = straight.Row;
    TColRowPoint::TCoordinate column
        = straight.Column + std::floor(static_cast<float>(straight.Row) / 2);;

    return TColRowPoint(column, row);
}


THexPoint::THexPoint(TCoordinate x, TCoordinate y, TCoordinate z)
    : X(x)
    , Y(y)
    , Z(z) {
    if (X + Y + Z != 0) {
        throw TException("Invalid hex point created at ")
            << __FILE__ << ":" << __LINE__;
    }
}

bool THexPoint::operator==(const THexPoint& other) const {
    return X == other.X && Y == other.Y && Z == other.Z;
}

bool THexPoint::operator!=(const THexPoint& other) const {
    return !operator==(other);
}

THexPoint ToHex(const TStraightColRowPoint& point) {
    THexPoint::TCoordinate x = point.Column;
    THexPoint::TCoordinate y = point.Row;
    THexPoint::TCoordinate z = - x - y;

    return THexPoint(x, y, z);
}

THexPoint ToHex(const TColRowPoint& point) {
    return ToHex(Straighten(point));
}

template <>
TStraightColRowPoint FromHex<TStraightColRowPoint>(const THexPoint& hex) {
    return TStraightColRowPoint(hex.X, hex.Y);
}

template <>
TColRowPoint FromHex<TColRowPoint>(const THexPoint& hex) {
    auto straigthPoint = FromHex<TStraightColRowPoint>(hex);
    return Unstraighten(straigthPoint);
}

} // namespace Coords
