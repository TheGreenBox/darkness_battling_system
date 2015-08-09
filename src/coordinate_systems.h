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
TColRowPoint FromHex(const THexPoint&);

} // namespace Coords
