#include "way_graph.h"
#include "board_metrics.h"
#include "exception.h"

#include <iostream>

TWayGraph::TWayGraph(
    Coords::TColRowPoint::TCoordinate rowShift,
    Coords::TColRowPoint::TCoordinate columnShift
)
    : RowShift(rowShift)
    , ColumnShift(columnShift)
{
}

void TWayGraph::Build(const TBoard& board, const TUnit& srcUnit) {
    TUnit unit = srcUnit.Clone();
    const size_t rows = board.GetRowCount() + 2 * RowShift;
    const size_t columns = board.GetColumnCount() + 2 * ColumnShift;
    Graph.resize(rows, TMatrixRow(columns));

    // jump to left up map corner
    unit = unit.TeleportTo(Coords::TColRowPoint(-ColumnShift, -RowShift));
    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            for (size_t turn = 0; turn < TurnDirections; ++turn) {
                if (board.UnitWillFitInside(unit)) {
                    auto& node = GetNode(
                        unit.GetPivot().GetPosition().Column,
                        unit.GetPivot().GetPosition().Row,
                        turn
                    );
                    node.Available = true;
                    node.Metrics = calulateMetrics(board, unit);
                }
                unit = unit.Move(EMoveOperations::ROTATE_ANTI_CLOCKWISE);
            }
            unit = unit.Move(EMoveOperations::SLIDE_EAST);
        }
        // jump to the start cell on the next row
        unit = unit.TeleportTo(Coords::TColRowPoint(
            -ColumnShift,
            unit.GetPivot().GetPosition().Row + 1
        ));
    }
}

TWayGraph TWayGraph::Clone() const {
    TWayGraph copy(RowShift, ColumnShift);
    copy.Graph = Graph;
    return std::move(copy);
}

std::vector<EMoveOperations>
TWayGraph::FindWay(const TSegment& from, const TSegment& to) {
    if (true) {
        throw TException("Not implemented");
    }
    return std::vector<EMoveOperations>(0);
}

TSegment TWayGraph::GetCoordinateFromIndex(size_t colInd, size_t rowInd) const {
    auto row = static_cast<TCoordinate>(rowInd) - RowShift;
    auto column = static_cast<TCoordinate>(colInd) - ColumnShift;
    return TSegment(Coords::TColRowPoint(column, row));
}

size_t TWayGraph::GetRowIndexFromCoordinate(
    Coords::TColRowPoint::TCoordinate row
) const {
    row += RowShift;
    if (row < 0) {
        throw TException("Wrong conversion: negative row index");
    }
    return static_cast<size_t>(row);
}

size_t TWayGraph::GetColumnIndexFromCoordinate(
    Coords::TColRowPoint::TCoordinate column
) const {
    column += RowShift;
    if (column < 0) {
        throw TException("Wrong conversion: negative column index");
    }
    return static_cast<size_t>(column);
}

bool
TWayGraph::CheckNode(
    TCoordinate column,
    TCoordinate row,
    size_t direction
) const {
    return GetNode(column, row, direction).Available;
}

TWayGraph::TNode&
TWayGraph::GetNode(
    TCoordinate column,
    TCoordinate row,
    size_t direction
) {
    size_t columnInd = GetRowIndexFromCoordinate(column);
    size_t rowInd = GetColumnIndexFromCoordinate(row);
    return Graph.at(rowInd).at(columnInd).at(direction);
}

const TWayGraph::TNode&
TWayGraph::GetNode(
    TCoordinate column,
    TCoordinate row,
    size_t direction
) const {
    size_t columnInd = GetRowIndexFromCoordinate(column);
    size_t rowInd = GetColumnIndexFromCoordinate(row);
    return Graph.at(rowInd).at(columnInd).at(direction);
}

std::string TWayGraph::ToString() const {
    std::ostringstream os(std::ios_base::ate);
    for (const auto& row : Graph) {
        for (size_t dir = 0; dir < TurnDirections; ++dir) {
            os << "   ";
            for (const auto& vert : row) {
                if (vert[dir].Available) {
                    os << "O";
                } else {
                    os << "X";
                }
            }
        }
        os << '\n';
    }
    return os.str();
}

