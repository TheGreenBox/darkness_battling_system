#pragma once

#include "move_operations.h"

#include "coordinate_systems.h"

#include <cstddef>

class TSegment {
public:
    TSegment() = delete;
    explicit TSegment(const Coords::ColRowPoint& position);

    TSegment Slide(EMoveOperations direction) const;
    TSegment TeleportBy(const Coords::ColRowPoint& delta) const;

    TSegment
    RotateAround(
        const Coords::ColRowPoint& pivot,
        EMoveOperations direction
    ) const;

    const Coords::ColRowPoint& GetPosition() const;

private:
    Coords::ColRowPoint Position;
};
