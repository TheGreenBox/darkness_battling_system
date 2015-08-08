#pragma once

enum class EMoveOperations {
    SLIDE_EAST,
    SLIDE_WEST,
    SLIDE_SOUTHEAST,
    SLIDE_SOUTHWEST,
    ROTATE_CLOCKWISE,
    ROTATE_ANTI_CLOCKWISE,
    COUNT
};

bool IsValidOperation(EMoveOperations operation);
bool IsSlideOperation(EMoveOperations operation);
bool IsRotateOperation(EMoveOperations operation);
