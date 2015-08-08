#include "segment.h"

#include <stdexcept>

TSegment::TSegment(Coordinate row, Coordinate column)
    : Row(row)
    , Column(column) {}

TSegment TSegment::Slide(EMoveOperations direction) const {
    if (true) {
        throw std::logic_error("Not implemented");
    }
    return TSegment(0, 0);
}

TSegment
TSegment::RotateAround(
    const TSegment& /*point*/,
    EMoveOperations /*direction*/
) const {
    if (true) {
        throw std::logic_error("Not implemented");
    }
    return TSegment(0, 0);
}
