#pragma once

#include "move_operations.h"

#include "coordinate_systems.h"

#include <cstddef>

class TSegment {
public:
    TSegment() = delete;
    explicit TSegment(const Coords::TColRowPoint& position);

    TSegment Slide(EMoveOperations direction) const;
    TSegment TeleportBy(const Coords::TColRowPoint& delta) const;

    TSegment
    RotateAround(
        const Coords::TColRowPoint& pivot,
        EMoveOperations direction
    ) const;

    const Coords::TColRowPoint& GetPosition() const;

private:
    Coords::TColRowPoint Position;
};
