#include "unit.h"

#include "exception.h"
#include "segment.h"

TUnit::TUnit(const TSegment& pivot, TSegments&& segments)
    : Pivot(pivot)
    , Segments(std::move(segments)) {}

TUnit TUnit::Move(EMoveOperations operation) const {
    if (IsSlideOperation(operation)) {
        return Slide(operation);
    }
    else if (IsRotateOperation(operation)) {
        return Rotate(operation);
    }
    else {
        throw TException("Invalid move operation recieved in ")
            << __FILE__ << ":" << __LINE__;
    }

    return Clone();
}

TUnit TUnit::Slide(EMoveOperations direction) const {
    TSegment newPivot = Pivot.Slide(direction);
    return TUnit(newPivot, SlideSegments(direction));
}

TUnit::TSegments TUnit::SlideSegments(EMoveOperations direction) const {
    TSegments ret;
    ret.reserve(Segments.size());
    for (const TSegment& segment : Segments) {
        TSegment slidedSegment = segment.Slide(direction);
        ret.push_back(slidedSegment);
    }

    return ret;
}

TUnit TUnit::TeleportTo(const Coords::ColRowPoint& newPivotPos) const {
    Coords::ColRowPoint oldPivotPos = Pivot.GetPosition();
    Coords::ColRowPoint delta(
        newPivotPos.Column - oldPivotPos.Column,
        newPivotPos.Row - oldPivotPos.Row
    );

    return TUnit(Pivot.TeleportBy(delta), TeleportSegments(delta));
}

TUnit::TSegments TUnit::TeleportSegments(const Coords::ColRowPoint& delta) const {
    TSegments ret;
    ret.reserve(Segments.size());
    for (const TSegment& segment : Segments) {
        TSegment teleportedSegment = segment.TeleportBy(delta);
        ret.push_back(teleportedSegment);
    }

    return ret;
}

TUnit TUnit::Rotate(EMoveOperations direction) const {
    return TUnit(Pivot, RotateSegments(direction));
}

TUnit::TSegments TUnit::RotateSegments(EMoveOperations direction) const {
    TSegments ret;
    ret.reserve(Segments.size());
    for (const TSegment& segment : Segments) {
        TSegment rotatedSegment = segment.RotateAround(
            Pivot.GetPosition(),
            direction
        );
        ret.push_back(rotatedSegment);
    }

    return ret;
}

const TUnit::TSegments& TUnit::GetSegments() const {
    return Segments;
}

const TSegment& TUnit::GetPivot() const {
    return Pivot;
}

TUnit TUnit::Clone() const {
    return TUnit(Pivot, TSegments(Segments));
}

