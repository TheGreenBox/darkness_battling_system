#pragma once

#include "move_operations.h"
#include "segment.h"

#include <cstddef>
#include <vector>

class TUnit {
public:
    using TSegments = std::vector<TSegment>;

    TUnit() = delete;
    TUnit(const TSegment& pivot, TSegments&& segments);

    TUnit(const TUnit&) = delete;
    TUnit& operator=(const TUnit&) = delete;

    TUnit(TUnit&&) = default;
    TUnit& operator=(TUnit&&) = default;

    /**
     * @details Handles EVERY movement operation internally
     */
    TUnit Move(EMoveOperations operation) const;
    TUnit TeleportTo(const Coords::ColRowPoint& newPivotPos) const;
    TUnit Clone() const;

    const TSegments& GetSegments() const;
    const TSegment& GetPivot() const;

private:
    TUnit Slide(EMoveOperations direction) const;
    TUnit Rotate(EMoveOperations direction) const;

    TSegments SlideSegments(EMoveOperations direction) const;
    TSegments RotateSegments(EMoveOperations direction) const;
    TSegments TeleportSegments(const Coords::ColRowPoint& delta) const;

    TSegment Pivot;
    TSegments Segments;
};
