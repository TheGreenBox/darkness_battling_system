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

TSegment
TSegment::RotateAround(
    const TSegment& /*point*/,
    EMoveOperations /*direction*/
) const {
    if (true) {
        throw TException("Not implemented");
    }
    return TSegment(Coords::ColRowPoint(0, 0));
}

const Coords::ColRowPoint& TSegment::GetPosition() const {
    return Position;
}
