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

bool TBoard::IsValidCell(size_t row, size_t column) const {
    return row < Cells.size() && column < GetColumnsNum();
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

    size_t columnsNum = GetColumnsNum();

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

    bool posIsNonNegative = position.Row >= 0 && position.Column >= 0;
    bool posIsInBoardBorders = IsValidCell(position.Row, position.Column);

    return posIsNonNegative && posIsInBoardBorders;
}

bool TBoard::SegmentPosIsLocked(const TSegment& segment) const {
    const auto& position = segment.GetPosition();
    return CellIsLocked(position.Row, position.Column);
}

size_t TBoard::GetColumnsNum() const {
    return Cells.empty() ? 0 : Cells.front().size();
}

std::string TBoard::ToString() const {
    const std::string border(GetColumnsNum(), '-');

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

TWayGraph::TWayGraph()
{
}

void Build(const TBoard& board, const TUnit& cunit) {
    unit = cunit.Clone();
    // range of scanning [ -3 , RowCount + 3    )
    //                   [ -3 , ColumnCount + 3 )
    const size_t reserve = 3;
    const size_t rows = board.GetRowCount() + 2 * reserve;
    const size_t columns = board.GetColumnCount() + 2 * reserve;
    Graph.resize(rows, TSurfaceRow(columns));

    TSegment scanStart(-reserve, -reserve);
    // TODO: teleportate unit to zero(?) point

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            for (size_t turn = 0; turn < TurnDirections; ++turn) {
                if (board.UnitWillFitInside(Unit)) {
                    Field.at(Unit.GetPivot().GetRow())
                         .at(Unit.GetPivot().GetColumn())
                         .at(turn)
                         .Occupied = false;
                }
                Unit.Move(EMoveOperations::ROTATE_ANTI_CLOCKWISE);
            }
            Unit.Move(EMoveOperations::SLIDE_EAST);
        }
        // TODO: teleportate unit to next row start point
    }
}

TWayGraph TWayGraph::clone() const {
    return TWayGraph(*this);
}
