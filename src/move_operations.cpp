bool IsValidOperation(EMoveOperations operation) {
    return operation < EMoveOperations::COUNT;
}

bool IsSlideOperation(EMoveOperations operation) {
    bool ret = false;
    switch (operation) {
        case EMoveOperations::SLIDE_EAST:
        case EMoveOperations::SLIDE_WEST:
        case EMoveOperations::SLIDE_SOUTHEAST:
        case EMoveOperations::SLIDE_SOUTHWEST: {
            ret = true;
            break;
        }
        default: {}
    }

    return ret;
}

bool IsRotateOperation(EMoveOperations operation) {
    bool ret = false;
    switch (operation) {
        case EMoveOperations::ROTATE_CLOCKWISE:
        case EMoveOperations::ROTATE_ANTI_CLOCKWISE: {
            ret = true;
            break;
        }
        default: {}
    }

    return ret;
}
