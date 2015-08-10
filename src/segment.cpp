#include "segment.h"

#include "exception.h"

TSegment::TSegment(const Coords::TColRowPoint& position)
    : Position(position) {}

bool TSegment::operator==(const TSegment& other) const {
    return Position == other.Position;
}

bool TSegment::operator!=(const TSegment& other) const {
    return !operator==(other);
}


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
            ++hexPos.Y;
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

TSegment TSegment::TeleportBy(const Coords::THexPoint& hexDelta) const {
    Coords::THexPoint oldHexPos = Coords::ToHex(Position);
    Coords::THexPoint newHexPos(
        oldHexPos.X + hexDelta.X,
        oldHexPos.Y + hexDelta.Y,
        oldHexPos.Z + hexDelta.Z
    );

    return TSegment(Coords::FromHex(newHexPos));
}

TSegment
TSegment::RotateAround(
    const Coords::TColRowPoint& pivot,
    EMoveOperations direction
) const {
    static const auto shiftCoordsLeft
        = [](const Coords::THexPoint& p) -> Coords::THexPoint {
        //    x y z
        // -> y z x
        return Coords::THexPoint(p.Y, p.Z, p.X);
    };
    static const auto shiftCoordsRight
        = [](const Coords::THexPoint& p) -> Coords::THexPoint {
        //    x y z
        // -> z x y
        return Coords::THexPoint(p.Z, p.X, p.Y);
    };
    static const auto invertSigns
        = [](const Coords::THexPoint& p) -> Coords::THexPoint {
        return Coords::THexPoint(-1* p.X, -1 * p.Y, -1 * p.Z);
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
            throw TException("Invalid rotation operation recieved in ")
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
