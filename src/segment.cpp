#include "segment.h"

#include "exception.h"

TSegment::TSegment(const Coords::TColRowPoint& position)
    : Position(position) {}

TSegment TSegment::Slide(EMoveOperations direction) const {
    Coords::THexPoint hexPos = Coords::ToHex(Position);

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

    Coords::TColRowPoint newPos = Coords::FromHex(hexPos);
    return TSegment(newPos);
}

TSegment TSegment::TeleportBy(const Coords::TColRowPoint& delta) const {
    Coords::TColRowPoint newPosition(
        Position.Column + delta.Column,
        Position.Row + delta.Row
    );

    return TSegment(newPosition);
}

TSegment
TSegment::RotateAround(
    const Coords::TColRowPoint& pivot,
    EMoveOperations direction
) const {
    static const auto shiftCoordsLeft
        = [](const Coords::THexPoint& point) -> Coords::THexPoint {
        //    x y z
        // -> y z x
        Coords::THexPoint::TCoordinate y = point.X;
        Coords::THexPoint::TCoordinate z = point.Y;
        Coords::THexPoint::TCoordinate x = point.Z;

        return Coords::THexPoint(x, y, z);
    };
    static const auto shiftCoordsRight
        = [](const Coords::THexPoint& point) -> Coords::THexPoint {
        //    x y z
        // -> z x y
        Coords::THexPoint::TCoordinate z = point.X;
        Coords::THexPoint::TCoordinate x = point.Y;
        Coords::THexPoint::TCoordinate y = point.Z;

        return Coords::THexPoint(x, y, z);
    };
    static const auto invertSigns
        = [](const Coords::THexPoint& point) -> Coords::THexPoint {
        Coords::THexPoint::TCoordinate x = -1 * point.X;
        Coords::THexPoint::TCoordinate y = -1 * point.Y;
        Coords::THexPoint::TCoordinate z = -1 * point.Z;

        return Coords::THexPoint(x, y, z);
    };

    Coords::THexPoint hexPivot = Coords::ToHex(pivot);
    Coords::THexPoint hexSelf = Coords::ToHex(Position);

    Coords::THexPoint hexSelfLocal(
        hexSelf.X - hexPivot.X,
        hexSelf.Y - hexPivot.Y,
        hexSelf.Z - hexPivot.Z
    );

    Coords::THexPoint newHexSelfLocal = hexSelfLocal;
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

    Coords::THexPoint newPosition(
        hexPivot.X + newHexSelfLocal.X,
        hexPivot.Y + newHexSelfLocal.Y,
        hexPivot.Z + newHexSelfLocal.Z
    );

    return TSegment(Coords::FromHex(newPosition));
}

const Coords::TColRowPoint& TSegment::GetPosition() const {
    return Position;
}
