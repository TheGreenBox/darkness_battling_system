#pragma once

#include "segment.h"
#include "unit.h"

#include <array>
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
    bool UnitWillFitInside(const TUnit& unit) const;

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

    bool SegmentPosIsOccupied(const TSegment& segment) const;

    static bool RowIsFullyLocked(const TStatusRow& row);

    TStatusCells Cells;
};

class TWayGraph {
public:
    TWayGraph(const TUnit& unit);
    TWayGraph(size_t rows, size_t columns, const TUnit& unit);

    TWayGraph() = delete;
    TWayGraph(const TWayGraph&) = delete;

    void Build(const TBoard& board, const TUnit& unit);

    enum class EColor {
        WHITE,
        GREY,
        BLACK
    };

    struct TNode {
        int Metrics = -1;
        EColor Color = EColor::WHITE;  // for dfs algo
        bool Occupied = true;

        operator bool() {
            return Occupied;
        }
    };

    TWayGraph clone() const;

private:
    static const size_t TurnDirections = 6;
    using TVertical = std::array<TNode, TurnDirections>;
    using TMatrixRow = std::vector<TVertical>;
    using TMatrix = std::vector<TMatrixRow>;

    TMatrix Graph;
};

