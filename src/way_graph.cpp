#include "way_graph.h"
#include "board_metrics.h"
#include "exception.h"

#include <iostream>
#include <limits>

TWayGraph::TWayGraph(
    Coords::TColRowPoint::TCoordinate rowShift,
    Coords::TColRowPoint::TCoordinate columnShift
)
    : RowShift(rowShift)
    , ColumnShift(columnShift)
    , FinishPoint(Coords::TColRowPoint(0, 0))  // FIXME
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
                    node.Metrics = CalulateMetrics(board, unit);
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

void
TWayGraph::FindPositionWithMinMetrics(
    TUnit& unit,
    size_t& fromDirection
) {
    int minMetrics = std::numeric_limits<int>::max();
    size_t minRow = -1;
    size_t minCol = -1;
    size_t minDir = -1;

    size_t rows = Graph.size();
    size_t columns = Graph.front().size();

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            for (size_t turn = 0; turn < TurnDirections; ++turn) {
                int metrics = Graph.at(row).at(column).at(turn).Metrics;
                if (metrics < minMetrics) {
                    minMetrics = metrics;
                    minRow = row;
                    minCol = column;
                    minDir = turn;
                }
            }
        }
    }

    fromDirection = minDir;

    Coords::TColRowPoint pivot(minCol, minRow);
    unit.TeleportTo(pivot);
    for (size_t rotationNum = 0; rotationNum < fromDirection; ++rotationNum) {
        unit.Move(EMoveOperations::ROTATE_ANTI_CLOCKWISE);
    }

    return;
}

TWayGraph::TWays
TWayGraph::FindWay(
    const Coords::TColRowPoint& from,
    size_t fromDirection,
    const Coords::TColRowPoint& to,
    size_t toDirection
) {
    FinishPoint = TSegment(to);
    FinishDirection = toDirection;

    Dfs(TSegment(from), fromDirection);
    return AllWays;
}

void TWayGraph::Dfs(
    const TSegment& point,
    size_t direction
) {
    if (!IsValid(point.GetPosition())) {
        return;
    }

    TNode& currentNode = GetNode(
        point.GetPosition().Column,
        point.GetPosition().Row,
        direction
    );

    if (!currentNode.Available) {
        return;
    }

    if (currentNode.Color == EColor::BLACK) {
        return;
    }

    if (point == FinishPoint && direction == FinishDirection) {
        AllWays.push_back(CurrentWay);
        return;
    }

    currentNode.Color = EColor::BLACK;

    CurrentWay.push_back(EMoveOperations::SLIDE_EAST);
    auto next = point.Slide(EMoveOperations::SLIDE_EAST);
    Dfs(next, direction);
    CurrentWay.pop_back();

    CurrentWay.push_back(EMoveOperations::SLIDE_WEST);
    next = point.Slide(EMoveOperations::SLIDE_WEST);
    Dfs(next, direction);
    CurrentWay.pop_back();

    CurrentWay.push_back(EMoveOperations::SLIDE_SOUTHEAST);
    next = point.Slide(EMoveOperations::SLIDE_SOUTHEAST);
    Dfs(next, direction);
    CurrentWay.pop_back();

    CurrentWay.push_back(EMoveOperations::SLIDE_SOUTHWEST);
    next = point.Slide(EMoveOperations::SLIDE_SOUTHWEST);
    Dfs(next, direction);
    CurrentWay.pop_back();

    CurrentWay.push_back(EMoveOperations::ROTATE_CLOCKWISE);
    if (direction == 0) {
        Dfs(point, TurnDirections - 1);
    } else {
        Dfs(point, direction - 1);
    }
    CurrentWay.pop_back();

    CurrentWay.push_back(EMoveOperations::ROTATE_ANTI_CLOCKWISE);
    if (direction == TurnDirections - 1) {
        Dfs(point, 0);
    } else {
        Dfs(point, direction + 1);
    }
    CurrentWay.pop_back();

    //currentNode.Color = EColor::WHITE;
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
    column += ColumnShift;
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

bool TWayGraph::IsValid(const Coords::TColRowPoint& pt) const {
    TCoordinate rowInd = pt.Row + RowShift;
    if (rowInd < 0 || rowInd > static_cast<TCoordinate>(Graph.size())) {
        return false;
    }
    TCoordinate columnInd = pt.Column + ColumnShift;
    if (columnInd < 0 || columnInd > static_cast<TCoordinate>(Graph.front().size())) {
        return false;
    }
    return true;
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

