#pragma once

#include <vector>

#include "segment.h"

class TUnit {
public:
    using TSegments = std::vector<TSegment>;

    TUnit() = delete;
    TUnit(const TSegment& pivot, TSegments&& segments);

    TUnit(const TUnit&) = delete;
    TUnit& operator=(const TUnit&) = delete;

    TUnit(TUnit&&) = default;
    TUnit& operator=(TUnit&&) = default;

    TUnit Slide(EMoveOperations direction) const;
    TUnit Rotate(EMoveOperations direction) const;

private:
    TSegments MoveSegments(EMoveOperations direction) const;
    TSegments RotateSegments(EMoveOperations direction) const;

    TSegment Pivot;
    TSegments Segments;
};
