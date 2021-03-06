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

    bool operator==(const TUnit&) const;
    bool operator!=(const TUnit&) const;

    /**
     * @details Handles EVERY movement operation internally
     */
    TUnit Move(EMoveOperations operation) const;
    TUnit TeleportTo(const Coords::TColRowPoint& newPivotPos) const;
    TUnit Clone() const;

    const TSegments& GetSegments() const;
    const TSegment& GetPivot() const;

    void DebugPrint() const;

private:
    TUnit Slide(EMoveOperations direction) const;
    TUnit Rotate(EMoveOperations direction) const;

    TSegments SlideSegments(EMoveOperations direction) const;
    TSegments RotateSegments(EMoveOperations direction) const;
    TSegments TeleportSegments(const Coords::THexPoint& hexDelta) const;

    TSegment Pivot;
    TSegments Segments;
};
