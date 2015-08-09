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
    TBoard(size_t columns, size_t rows);

    void LockCell(size_t column, size_t row);
    void UnlockCell(size_t column, size_t row);

    bool CellIsLocked(size_t column, size_t row) const;
    bool UnitWillFitInside(const TUnit& unit) const;

    size_t CollapseRows();

    std::string ToString() const;

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

    bool SegmentPosIsValid(const TSegment& segment) const;
    bool SegmentPosIsLocked(const TSegment& segment) const;

    size_t GetColumnsNum() const;

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
    Coords::ColRowPoint::Coordinate RowShift;
    Coords::ColRowPoint::Coordinate ColumnShift;
};

