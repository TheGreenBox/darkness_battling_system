#pragma once

#include "coordinate_systems.h"
#include "segment.h"
#include "unit.h"

#include <array>
#include <cstddef>
#include <vector>
#include <string>

class TBoard {
public:
    TBoard() = delete;
    TBoard(size_t columns, size_t rows);

    void LockCell(size_t column, size_t row);
    void UnlockCell(size_t column, size_t row);
    void LockCells(const TUnit&);

    bool CellIsLocked(size_t column, size_t row) const;
    bool UnitWillFitInside(const TUnit& unit) const;
    bool SegmentPosIsValid(const TSegment& segment) const;
    bool SegmentPosIsLocked(const TSegment& segment) const;

    size_t CollapseRows();

    std::string ToString() const;

    size_t GetRowCount() const;
    size_t GetColumnCount() const;

private:
    using Status = bool;
    using TStatusRow = std::vector<Status>;
    using TStatusCells = std::vector<TStatusRow>;

    static const Status CELL_IS_LOCKED;
    static const Status CELL_IS_UNLOCKED;

    void SetCellStatus(size_t column, size_t row, Status newStatus);
    bool IsValidCell(size_t column, size_t row) const;

    TStatusCells::iterator
    NextLockedRow(
        TStatusCells::iterator searchStart
    );
    void ShiftDownAllRowsAboveOnce(TStatusCells::iterator& shiftBorderIter);

    static bool RowIsFullyLocked(const TStatusRow& row);

    TStatusCells Cells;
};

