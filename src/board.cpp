#include "board.h"

bool TBoard::CELL_IS_LOCKED = true;
bool TBoard::CELL_IS_UNLOCKED = false;

TBoard::TBoard(size_t rows, size_t columns)
    : CellsStatuses(rows, TRow(columns, CELL_IS_UNLOCKED)) {}

void TBoard::LockCell(size_t row, size_t column) {
    SetCellStatus(row, column, CELL_IS_LOCKED);
}

void TBoard::SetCellStatus(size_t row, size_t column, bool newStatus) {
    auto& status = CellsStatuses.at(row).at(column);
    status = newStatus;
}

void TBoard::UnlockCell(size_t row, size_t column) {
    SetCellStatus(row, column, CELL_IS_UNLOCKED);
}

bool TBoard::CellIsLocked(size_t row, size_t column) const {
    return CellsStatuses.at(row).at(column) == CELL_IS_LOCKED;
}
