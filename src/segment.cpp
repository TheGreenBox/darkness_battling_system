#include "segment.h"

#include "exception.h"

TSegment::TSegment(Coordinate row, Coordinate column)
    : Row(row)
    , Column(column) {}

TSegment TSegment::Slide(EMoveOperations direction) const {
    if (!IsSlideOperation(direction)) {
        throw TException("Invalid slide operation recieved in ")
            << __FILE__ << ":" << __LINE__;
    }

    TSegment::Coordinate rowDelta = 0;
    TSegment::Coordinate columnDelta = 0;

    if (direction == EMoveOperations::SLIDE_EAST) {
        rowDelta = 1;
    }
    else if (direction == EMoveOperations::SLIDE_WEST) {
        rowDelta = -1;
    }
    else if (direction == EMoveOperations::SLIDE_SOUTHEAST) {
        rowDelta = 1;
        columnDelta = 1;
    }
    else if (direction == EMoveOperations::SLIDE_SOUTHWEST) {
        columnDelta = 1;
    }

    return TSegment(Row + rowDelta, Column + columnDelta);
}

TSegment
TSegment::RotateAround(
    const TSegment& /*point*/,
    EMoveOperations /*direction*/
) const {
    if (true) {
        throw TException("Not implemented");
    }
    return TSegment(0, 0);
}

TSegment::Coordinate TSegment::GetRow() const {
    return Row;
}

TSegment::Coordinate TSegment::GetColumn() const {
    return Column;
}

