enum class EMoveOperations {
    SLIDE_EAST,
    SLIDE_WEST,
    SLIDE_SOUTHEAST,
    SLIDE_SOUTHWEST,
    ROTATE_CLOCKWISE,
    ROTATE_ANTI_CLOCKWISE,
    COUNT
};

bool isValidOperation(EMoveOperations operation);
bool isSlideOperation(EMoveOperations operation);
bool isRotateOperation(EMoveOperations operation);
