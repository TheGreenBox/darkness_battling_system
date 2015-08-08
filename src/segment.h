#pragma once

#include "move_operations.h"

#include <cstddef>

class TSegment {
public:
    using Coordinate = int;

    TSegment() = delete;
    TSegment(Coordinate row, Coordinate column);

    TSegment Slide(EMoveOperations direction) const;

    TSegment
    RotateAround(
        const TSegment& point,
        EMoveOperations direction
    ) const;

    Coordinate GetRow() const;
    Coordinate GetColumn() const;

private:
    Coordinate Row;
    Coordinate Column;
};
