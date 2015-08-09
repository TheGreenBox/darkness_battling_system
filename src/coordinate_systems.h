#pragma once

namespace Coords {

struct RowColPoint {
    using Coordinate = int;

    RowColPoint(Coordinate column, Coordinate row);

    bool operator==(const RowColPoint&) const;
    bool operator!=(const RowColPoint&) const;

    Coordinate Column;
    Coordinate Row;
};

struct StraightRowColPoint {
    using Coordinate = RowColPoint::Coordinate;

    StraightRowColPoint(Coordinate column, Coordinate row);

    bool operator==(const StraightRowColPoint&) const;
    bool operator!=(const StraightRowColPoint&) const;

    Coordinate Column;
    Coordinate Row;
};

StraightRowColPoint Straighten(const RowColPoint&);
RowColPoint Unstraighten(const StraightRowColPoint&);


struct HexPoint {
    using Coordinate = RowColPoint::Coordinate;

    HexPoint(Coordinate x, Coordinate y, Coordinate z);

    bool operator==(const HexPoint&) const;
    bool operator!=(const HexPoint&) const;

    Coordinate X;
    Coordinate Y;
    Coordinate Z;
};

HexPoint ToHex(const RowColPoint&);
HexPoint ToHex(const StraightRowColPoint&);

template <typename RetType>
RetType FromHex(const HexPoint&);

} // namespace Coords
