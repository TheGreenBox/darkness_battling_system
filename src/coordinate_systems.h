#pragma once

namespace Coords {

struct ColRowPoint {
    using Coordinate = int;

    ColRowPoint(Coordinate column, Coordinate row);

    bool operator==(const ColRowPoint&) const;
    bool operator!=(const ColRowPoint&) const;

    Coordinate Column;
    Coordinate Row;
};

struct StraightColRowPoint {
    using Coordinate = ColRowPoint::Coordinate;

    StraightColRowPoint(Coordinate column, Coordinate row);

    bool operator==(const StraightColRowPoint&) const;
    bool operator!=(const StraightColRowPoint&) const;

    Coordinate Column;
    Coordinate Row;
};

StraightColRowPoint Straighten(const ColRowPoint&);
ColRowPoint Unstraighten(const StraightColRowPoint&);


struct HexPoint {
    using Coordinate = ColRowPoint::Coordinate;

    HexPoint(Coordinate x, Coordinate y, Coordinate z);

    bool operator==(const HexPoint&) const;
    bool operator!=(const HexPoint&) const;

    Coordinate X;
    Coordinate Y;
    Coordinate Z;
};

HexPoint ToHex(const ColRowPoint&);
HexPoint ToHex(const StraightColRowPoint&);

template <typename RetType>
RetType FromHex(const HexPoint&);

} // namespace Coords
