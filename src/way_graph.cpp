#include "way_graph.h"

TWayGraph::TWayGraph(
    Coords::ColRowPoint::Coordinate RowShift,
    Coords::ColRowPoint::Coordinate ColumnShift
)
    : RowShift(rowShift)
    , ColumnShift(columnShift)
{
}

void Build(const TBoard& board, const TUnit& srcUnit) {
    unit = srcUnit.Clone();

    const size_t rows = board.GetRowCount() + 2 * RowShift;
    const size_t columns = board.GetColumnCount() + 2 * ColumnShift;
    Graph.resize(rows, TSurfaceRow(columns));

    unit.TeleportTo(Coords::ColRowPoint(-ColumnShift, -RowShift));

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            for (size_t turn = 0; turn < TurnDirections; ++turn) {
                if (board.UnitWillFitInside(Unit)) {
                    size_t row = GetRowIndexFromCoordinate(
                        Unit.GetPivot().GetRow()
                    );
                    size_t column = GetColumnIndexFromCoordinate(
                        Unit.GetPivot().GetColumn()
                    );
                    Graph.at(row).at(column).at(turn).Occupied = false;
                }
                Unit.Move(EMoveOperations::ROTATE_ANTI_CLOCKWISE);
            }
            Unit.Move(EMoveOperations::SLIDE_EAST);
        }
        if (row % 2 != 0) {
            Unit.Move(EMoveOperations::SLIDE_SOUTHEAST);
        } else {
            Unit.Move(EMoveOperations::SLIDE_SOUTHWEST);
        }
    }
}

TWayGraph TWayGraph::Clone() const {
    TWayGraph copy(RowShift, ColumnShift);
    copy.Graph = Graph;
    return copy;
}

std::vector<EMoveOperations>
TWayGraph::FindWay(const TSegment& from, const TSegment& to) {
    if (true) {
        throw TException("Not implemented");
    }
    return std::vector<EMoveOperations>(0);
}

TSegment TWayGraph::GetCoordinateFromIndex(size_t colInd, size_t rowInd) {
    Coordinate row = static_cast<Coordinate>(rowInd) - RowShift;
    Coordinate column = static_cast<Coordinate>(column) - ColumnShift;
    return TSegment(column, row);
}

size_t TWayGraph::GetRowIndexFromCoordinate(
    Coords::ColRowPoint::Coordinate row
) {
    row += RowShift;
    if (row < 0) {
        throw TException("Wrong conversion: negative row index");
    }
    return static_cast<size_t>(row);
}

size_t TWayGraph::GetColumnIndexFromCoordinate(
    Coords::ColRowPoint::Coordinate column
) {
    column += RowShift;
    if (column < 0) {
        throw TException("Wrong conversion: negative column index");
    }
    return static_cast<size_t>(column);
}
