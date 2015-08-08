#include "board.h"

bool TBoard::IS_LOCKED = true;
bool TBoard::IS_UNLOCKED = false;

TBoard::TBoard(size_t rows, size_t columns)
    : SegmentsStatuses(rows, TRow(columns, IS_UNLOCKED)) {}

void TBoard::LockSegment(size_t row, size_t column) {
    SetSegmentStatus(row, column, IS_LOCKED);
}

void TBoard::SetSegmentStatus(size_t row, size_t column, bool newStatus) {
    auto& status = SegmentsStatuses.at(row).at(column);
    status = newStatus;
}

void TBoard::UnlockSegment(size_t row, size_t column) {
    SetSegmentStatus(row, column, IS_LOCKED);
}

bool TBoard::SegmentIsLocked(size_t row, size_t column) const {
    return SegmentsStatuses.at(row).at(column) == IS_LOCKED;
}
