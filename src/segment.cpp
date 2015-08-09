#include "segment.h"

#include "exception.h"

TSegment::TSegment(const Coords::ColRowPoint& position)
    : Position(position) {}

TSegment TSegment::Slide(EMoveOperations direction) const {
    Coords::HexPoint hexPos = Coords::ToHex(Position);

    switch (direction) {
        case EMoveOperations::SLIDE_EAST: {
            ++hexPos.X;
            --hexPos.Z;
            break;
        }
        case EMoveOperations::SLIDE_WEST: {
            --hexPos.X;
            ++hexPos.Z;
            break;
        }
        case EMoveOperations::SLIDE_SOUTHEAST: {
            --hexPos.Z;
            --hexPos.Y;
            break;
        }
        case EMoveOperations::SLIDE_SOUTHWEST: {
            --hexPos.X;
            ++hexPos.Y;
            break;
        }
        default: {
            throw TException("Invalid slide operation recieved in ")
                << __FILE__ << ":" << __LINE__;
        }
    }

    Coords::ColRowPoint newPos = Coords::FromHex<Coords::ColRowPoint>(hexPos);
    return TSegment(newPos);
}

TSegment TSegment::TeleportBy(const Coords::ColRowPoint& delta) const {
    Coords::ColRowPoint newPosition(
        Position.Column + delta.Column,
        Position.Row + delta.Row
    );

    return TSegment(newPosition);
}

TSegment
TSegment::RotateAround(
    const Coords::ColRowPoint& pivot,
    EMoveOperations direction
) const {
    static const auto shiftCoordsLeft
        = [](const Coords::HexPoint& point) -> Coords::HexPoint {
        //    x y z
        // -> y z x
        Coords::HexPoint::Coordinate y = point.X;
        Coords::HexPoint::Coordinate z = point.Y;
        Coords::HexPoint::Coordinate x = point.Z;

        return Coords::HexPoint(x, y, z);
    };
    static const auto shiftCoordsRight
        = [](const Coords::HexPoint& point) -> Coords::HexPoint {
        //    x y z
        // -> z x y
        Coords::HexPoint::Coordinate z = point.X;
        Coords::HexPoint::Coordinate x = point.Y;
        Coords::HexPoint::Coordinate y = point.Z;

        return Coords::HexPoint(x, y, z);
    };
    static const auto invertSigns
        = [](const Coords::HexPoint& point) -> Coords::HexPoint {
        Coords::HexPoint::Coordinate x = -1 * point.X;
        Coords::HexPoint::Coordinate y = -1 * point.Y;
        Coords::HexPoint::Coordinate z = -1 * point.Z;

        return Coords::HexPoint(x, y, z);
    };

    Coords::HexPoint hexPivot = Coords::ToHex(pivot);
    Coords::HexPoint hexSelf = Coords::ToHex(Position);

    Coords::HexPoint hexSelfLocal(
        hexSelf.X - hexPivot.X,
        hexSelf.Y - hexPivot.Y,
        hexSelf.Z - hexPivot.Z
    );

    Coords::HexPoint newHexSelfLocal = hexSelfLocal;
    switch (direction) {
        case EMoveOperations::ROTATE_CLOCKWISE: {
            newHexSelfLocal = invertSigns(shiftCoordsLeft(hexSelfLocal));
            break;
        }
        case EMoveOperations::ROTATE_ANTI_CLOCKWISE: {
            newHexSelfLocal = invertSigns(shiftCoordsRight(hexSelfLocal));
            break;
        }
        default: {
            throw TException("Invalid rotate operation recieved in ")
                << __FILE__ << ":" << __LINE__;
        }
    }

    Coords::HexPoint newPosition(
        hexPivot.X + newHexSelfLocal.X,
        hexPivot.Y + newHexSelfLocal.Y,
        hexPivot.Z + newHexSelfLocal.Z
    );

    return TSegment(Coords::FromHex<Coords::ColRowPoint>(newPosition));
}

const Coords::ColRowPoint& TSegment::GetPosition() const {
    return Position;
}
