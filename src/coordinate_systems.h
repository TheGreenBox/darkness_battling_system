#pragma once

namespace Coords {

struct TColRowPoint {
    using TCoordinate = int;

    TColRowPoint(TCoordinate column, TCoordinate row);

    bool operator==(const TColRowPoint&) const;
    bool operator!=(const TColRowPoint&) const;

    TCoordinate Column;
    TCoordinate Row;
};

struct TStraightColRowPoint {
    using TCoordinate = TColRowPoint::TCoordinate;

    TStraightColRowPoint(TCoordinate column, TCoordinate row);

    bool operator==(const TStraightColRowPoint&) const;
    bool operator!=(const TStraightColRowPoint&) const;

    TCoordinate Column;
    TCoordinate Row;
};

TStraightColRowPoint Straighten(const TColRowPoint&);
TColRowPoint Unstraighten(const TStraightColRowPoint&);


struct THexPoint {
    using TCoordinate = TColRowPoint::TCoordinate;

    THexPoint(TCoordinate x, TCoordinate y, TCoordinate z);

    bool operator==(const THexPoint&) const;
    bool operator!=(const THexPoint&) const;

    TCoordinate X;
    TCoordinate Y;
    TCoordinate Z;
};

THexPoint ToHex(const TColRowPoint&);
THexPoint ToHex(const TStraightColRowPoint&);

template <typename RetType>
RetType FromHex(const THexPoint&);

} // namespace Coords
