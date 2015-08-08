#pragma once

#include <cstddef>
#include <vector>

class TBoard {
public:
    TBoard(size_t rows, size_t columns);

    void LockCell(size_t row, size_t column);
    void UnlockCell(size_t row, size_t column);

    bool CellIsLocked(size_t row, size_t column) const;

private:
    using TRow = std::vector<bool>;
    using TCells = std::vector<TRow>;

    static bool CELL_IS_LOCKED;
    static bool CELL_IS_UNLOCKED;

    void SetCellStatus(size_t row, size_t column, bool newStatus);

    TCells CellsStatuses;
};
