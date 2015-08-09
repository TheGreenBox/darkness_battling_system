#include "board_metrics.h"

#include <iostream>

namespace {

bool CellStatusChangesInDirection(
    const TBoard& board,
    const TSegment& from,
    EMoveOperations to
) {
    const auto& fromPos = from.GetPosition();
    bool status1 = board.CellIsLocked(fromPos.Column, fromPos.Row);
    TSegment afterMove = from.Slide(to);

    if (board.SegmentPosIsValid(afterMove)) {
        const auto& afterMovePos = afterMove.GetPosition();
        bool status2 = board.CellIsLocked(afterMovePos.Column, afterMovePos.Row);

        return status1 != status2;
    }

    return false;
}

} // unnamed namespace

int calulateMetrics(const TBoard& board, const TUnit& unit) {
    TBoard modifiedBoard(board);

    for (const auto& segment : unit.GetSegments()) {
        const auto& position = segment.GetPosition();
        modifiedBoard.LockCell(position.Column, position.Row);
    }

    size_t numOfRowTransitions = 0;
    size_t numOfSouthEastTransitions = 0;
    size_t numOfSouthWestTransitions = 0;

    for (size_t columnNum = 0; columnNum < modifiedBoard.GetColumnCount(); ++columnNum) {
        for (size_t rowNum = 0; rowNum < modifiedBoard.GetRowCount(); ++rowNum) {
            TSegment segment(Coords::TColRowPoint(columnNum, rowNum));

            bool rowTransitionPresent = CellStatusChangesInDirection(
                modifiedBoard,
                segment,
                EMoveOperations::SLIDE_EAST
            );
            bool seTransitionPresent = CellStatusChangesInDirection(
                modifiedBoard,
                segment,
                EMoveOperations::SLIDE_SOUTHEAST
            );
            bool swTransitionPresent = CellStatusChangesInDirection(
                modifiedBoard,
                segment,
                EMoveOperations::SLIDE_SOUTHWEST
            );

            numOfRowTransitions += rowTransitionPresent ? 1 : 0;
            numOfSouthEastTransitions += seTransitionPresent ? 1 : 0;
            numOfSouthWestTransitions += swTransitionPresent ? 1 : 0;
        }
    }

    size_t rowsCollaped = modifiedBoard.CollapseRows();


    int ret = -3.2178882868487753 * numOfRowTransitions
        + -4.674347653 * numOfSouthEastTransitions
        + -4.674347653 * numOfSouthWestTransitions
        + 3.4181268101392694 * rowsCollaped;

    std::cout << "Metrics: " << ret << std::endl;
    std::cout << rowsCollaped << " " << numOfRowTransitions << " "
        << numOfSouthEastTransitions << " "
        << numOfSouthWestTransitions << std::endl;

    return ret;
}
