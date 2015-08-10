#pragma once

#include "move_operations.h"

#include "coordinate_systems.h"

#include <cstddef>

class TSegment {
public:
    TSegment() = delete;
    explicit TSegment(const Coords::TColRowPoint& position);

    bool operator==(const TSegment&) const;
    bool operator!=(const TSegment&) const;

    TSegment Slide(EMoveOperations direction) const;
    TSegment TeleportBy(const Coords::THexPoint& hexDelta) const;

    TSegment
    RotateAround(
        const Coords::TColRowPoint& pivot,
        EMoveOperations direction
    ) const;

    const Coords::TColRowPoint& GetPosition() const;

private:
    Coords::TColRowPoint Position;
};
