#include "board.h"

#include "exception.h"

#include <algorithm>

const TBoard::Status TBoard::CELL_IS_LOCKED = true;
const TBoard::Status TBoard::CELL_IS_UNLOCKED = false;

TBoard::TBoard(size_t rows, size_t columns)
    : Cells(rows, TStatusRow(columns, CELL_IS_UNLOCKED)) {}

void TBoard::LockCell(size_t row, size_t column) {
    SetCellStatus(row, column, CELL_IS_LOCKED);
}

void TBoard::SetCellStatus(size_t row, size_t column, Status newStatus) {
    Cells.at(row).at(column) = newStatus;
}

void TBoard::UnlockCell(size_t row, size_t column) {
    SetCellStatus(row, column, CELL_IS_UNLOCKED);
}

bool TBoard::CellIsLocked(size_t row, size_t column) const {
    return Cells.at(row).at(column) == CELL_IS_LOCKED;
}

size_t TBoard::CollapseRows() {
    size_t collapsedCount = 0;

    for (auto lockedRowIter = NextLockedRow(Cells.begin());
        lockedRowIter != Cells.end();
        lockedRowIter = NextLockedRow(std::next(lockedRowIter))
    ) {
        ShiftDownAllRowsAboveOnce(lockedRowIter);
        ++collapsedCount;
    }

    return collapsedCount;
}

TBoard::TStatusCells::iterator
TBoard::NextLockedRow(
    TStatusCells::iterator searchStart
) {
    return std::find_if(searchStart, Cells.end(), RowIsFullyLocked);
}

void TBoard::ShiftDownAllRowsAboveOnce(TStatusCells::iterator& shiftBorderIter) {
    if (shiftBorderIter == Cells.end()) {
        throw TException("Can not shift below lowest row")
            << __FILE__ << ":" << __LINE__;
    }

    using TReverseIter = std::reverse_iterator<TStatusCells::iterator>;
    // NOTE: reversing iterator makes it to point one element before
    for (TReverseIter toShiftIter(shiftBorderIter); toShiftIter != Cells.rend();
        toShiftIter = std::next(toShiftIter)) {
        TStatusRow& toShift = *toShiftIter;
        TStatusRow& newPosition = *std::prev(toShiftIter);
        newPosition = std::move(toShift);
    }

    Cells.front() = TStatusRow(Cells.back().size(), CELL_IS_UNLOCKED);
}

bool TBoard::RowIsFullyLocked(const TStatusRow& row) {
    auto result = std::find(row.begin(), row.end(), CELL_IS_UNLOCKED);
    return result == row.end();
}

bool TBoard::UnitWillFitInside(const TUnit& unit) const {
    for (const auto& segment : unit.GetSegments()) {
        if (SegmentPosIsOccupied(segment)) {
            return false;
        }
    }

    return true;
}

bool TBoard::SegmentPosIsOccupied(const TSegment& segment) const {
    return CellIsLocked(segment.GetRow(), segment.GetColumn());
}

std::string TBoard::ToString() const {
    const size_t borderLen = Cells.empty() ? 1 : Cells.front().size();
    const std::string border(borderLen, '-');

    std::string ret;

    ret += border;
    ret += '\n';
    for (const auto& row : Cells) {
        for (bool cellStatus : row) {
            ret += cellStatus == CELL_IS_UNLOCKED ? 'O' : 'X';
        }
        ret += '\n';
    }
    ret += border;
    ret += '\n';

    return ret;
}
