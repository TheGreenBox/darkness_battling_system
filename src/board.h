#pragma once

#include <cstddef>
#include <vector>
#include <string>

class TBoard {
public:
    TBoard() = delete;
    TBoard(size_t rows, size_t columns);

    void LockCell(size_t row, size_t column);
    void UnlockCell(size_t row, size_t column);

    bool CellIsLocked(size_t row, size_t column) const;

    size_t CollapseRows();

    std::string ToString() const;

private:
    using Status = bool;
    using TStatusRow = std::vector<Status>;
    using TStatusCells = std::vector<TStatusRow>;

    static const Status CELL_IS_LOCKED;
    static const Status CELL_IS_UNLOCKED;

    void SetCellStatus(size_t row, size_t column, Status newStatus);

    TStatusCells::iterator
    NextLockedRow(
        TStatusCells::iterator searchStart
    );
    void ShiftDownAllRowsAboveOnce(TStatusCells::iterator& shiftBorderIter);

    static bool RowIsFullyLocked(const TStatusRow& row);

    TStatusCells Cells;
};
