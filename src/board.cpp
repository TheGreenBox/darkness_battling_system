#include "board.h"

#include "exception.h"

#include <algorithm>
#include <iostream>

const TBoard::Status TBoard::CELL_IS_LOCKED = true;
const TBoard::Status TBoard::CELL_IS_UNLOCKED = false;

TBoard::TBoard(size_t columns, size_t rows)
    : Cells(rows, TStatusRow(columns, CELL_IS_UNLOCKED)) {}

void TBoard::LockCell(size_t column, size_t row) {
    SetCellStatus(column, row, CELL_IS_LOCKED);
}

void TBoard::SetCellStatus(size_t column, size_t row, Status newStatus) {
    Cells.at(row).at(column) = newStatus;
}

void TBoard::LockCells(const TUnit& unit) {
    for (const auto& segment : unit.GetSegments()) {
        const auto& position = segment.GetPosition();
        LockCell(position.Column, position.Row);
    }
}

void TBoard::UnlockCell(size_t column, size_t row) {
    SetCellStatus(column, row, CELL_IS_UNLOCKED);
}

bool TBoard::CellIsLocked(size_t column, size_t row) const {
    return Cells.at(row).at(column) == CELL_IS_LOCKED;
}

bool TBoard::IsValidCell(size_t column, size_t row) const {
    return column < GetColumnCount() && row < Cells.size();
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

    size_t columnsNum = GetColumnCount();

    using TReverseIter = std::reverse_iterator<TStatusCells::iterator>;
    // NOTE: reversing iterator makes it to point one element before
    for (TReverseIter toShiftIter(shiftBorderIter); toShiftIter != Cells.rend();
        toShiftIter = std::next(toShiftIter)) {
        TStatusRow& toShift = *toShiftIter;
        TStatusRow& newPosition = *std::prev(toShiftIter);
        newPosition = std::move(toShift);
    }

    Cells.front() = TStatusRow(columnsNum, CELL_IS_UNLOCKED);
}

bool TBoard::RowIsFullyLocked(const TStatusRow& row) {
    auto result = std::find(row.begin(), row.end(), CELL_IS_UNLOCKED);
    return result == row.end();
}

bool TBoard::UnitWillFitInside(const TUnit& unit) const {
    for (const auto& segment : unit.GetSegments()) {
        if (!SegmentPosIsValid(segment) || SegmentPosIsLocked(segment)) {
            return false;
        }
    }

    return true;
}

bool TBoard::SegmentPosIsValid(const TSegment& segment) const {
    const auto& position = segment.GetPosition();

    bool posIsNonNegative = position.Column >= 0 && position.Row >= 0;
    bool posIsInBoardBorders = IsValidCell(position.Column, position.Row);

    return posIsNonNegative && posIsInBoardBorders;
}

bool TBoard::SegmentPosIsLocked(const TSegment& segment) const {
    const auto& position = segment.GetPosition();
    return CellIsLocked(position.Column, position.Row);
}

TUnit TBoard::TeleportUnitToSpawnPosition(const TUnit& unit) const {
    Coords::TColRowPoint::TCoordinate left =
        std::numeric_limits<Coords::TColRowPoint::TCoordinate>::max();
    Coords::TColRowPoint::TCoordinate right =
        std::numeric_limits<Coords::TColRowPoint::TCoordinate>::min();

    for (const auto& segment : unit.GetSegments()) {
        if (segment.GetPosition().Column > right) {
            right = segment.GetPosition().Column;
        }
        if (segment.GetPosition().Column < left) {
            left = segment.GetPosition().Column;
        }
    }
    Coords::TColRowPoint::TCoordinate middle = (right - left) / 2;
    Coords::TColRowPoint::TCoordinate shift = (GetColumnCount() + 1)/2 - 1 - middle;

    return unit.TeleportTo(
        Coords::TColRowPoint(
            unit.GetPivot().GetPosition().Column + shift,
            unit.GetPivot().GetPosition().Row
        )
    );
}

size_t TBoard::GetColumnCount() const {
    return Cells.empty() ? 0 : Cells.front().size();
}

size_t TBoard::GetRowCount() const {
    return Cells.size();
}

std::string TBoard::ToString() const {
    const std::string border(GetColumnCount(), '-');

    std::string ret;

    ret += border;
    ret += '\n';
    int rowNum = 0;
    for (const auto& row : Cells) {
        if ((rowNum % 2) != 0) {
            ret += ' ';
        }
        ++rowNum;
        for (bool cellStatus : row) {
            ret += cellStatus == CELL_IS_UNLOCKED ? ". " : "O ";
        }
        ret += '\n';
    }
    ret += border;
    ret += '\n';

    return ret;
}
