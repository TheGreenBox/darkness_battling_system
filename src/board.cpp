#include <algorithm>

#include "board.h"

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
    if (!Cells.empty()) {
        while (RowIsFullyLocked(Cells.back())) {
            auto placeToMoveRow = Cells.rbegin();
            auto rowToMove = std::next(placeToMoveRow);

            while (rowToMove != Cells.rend()) {
                *placeToMoveRow = std::move(*rowToMove);

                placeToMoveRow = std::next(placeToMoveRow);
                rowToMove = std::next(rowToMove);
            }

            TStatusRow& topRow = Cells.back();
            topRow = TStatusRow(topRow.size(), CELL_IS_UNLOCKED);

            ++collapsedCount;
        }
    }

    return collapsedCount;
}

bool TBoard::RowIsFullyLocked(const TStatusRow& row) {
    auto result = std::find(row.begin(), row.end(), CELL_IS_UNLOCKED);
    return result == row.end();
}