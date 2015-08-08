#pragma once

#include "move_operations.h"

class TSegment {
public:
    TSegment() = delete;
    TSegment(size_t row, size_t column);

    TSegment Slide(EMoveOperations direction) const;

    TSegment
    RotateAround(
        const TSegment& point,
        EMoveOperations direction
    ) const;

private:
    size_t Row;
    size_t Column;
};
