#include "exception.h"
#include "segment.h"
#include "way_graph.h"

#include <iostream>

void TestBuildGraph() {
    TBoard board(3, 3);
    /*  XXO
        OOO
        OOO */
    board.LockCell(0, 0);
    board.LockCell(1, 0);

    TUnit::TSegments segments = {
        TSegment(Coords::TColRowPoint(0, 0)),
        TSegment(Coords::TColRowPoint(1, 0)),
    };

    /*  xX */
    TUnit unit(
        TSegment(Coords::TColRowPoint(0, 0)),
        std::move(segments)
    );

    TWayGraph graph(1, 1);
    graph.Build(board, unit);
    std::string rightGraphText = ""
        "   XXXXX   XXXXX   XXXXX   XXXXX   XXXXX   XXXXX\n"
        "   XXXXX   XXXXX   XXXXX   XXXXX   XXXOX   XXXOX\n"
        "   XOOXX   XXOXX   XXXOX   XXOOX   XOOOX   XOOXX\n"
        "   XOOXX   XOOOX   XXOOX   XXOOX   XXXXX   XXXXX\n"
        "   XXXXX   XXXXX   XXXXX   XXXXX   XXXXX   XXXXX\n"
    ;
    std::string graphText = graph.ToString();
    if (graphText != rightGraphText) {
        throw TException("Wrong answer")
            << __FILE__ << ":" << __LINE__
            << " :\n" << graphText << "\n"
            << "expected:\n" << rightGraphText
        ;
    }

    if (graph.CheckNode(0, 0, 0)) {
        throw TException("Wrong answer")
            << __FILE__ << ":" << __LINE__;
    }

    if (!graph.CheckNode(0, 1, 0)) {
        throw TException("Wrong answer")
            << __FILE__ << ":" << __LINE__;
    }
}

void TestFindWay() {
    TBoard board(3, 4);
    /*  OOO
        XOX
        OOO
        OOX */
    board.LockCell(0, 1);
    board.LockCell(2, 1);
    board.LockCell(2, 3);

    TUnit::TSegments segments = {
        TSegment(Coords::TColRowPoint(0, 0)),
        TSegment(Coords::TColRowPoint(1, 0)),
    };

    /*  xX */
    TUnit unit(
        TSegment(Coords::TColRowPoint(0, 0)),
        std::move(segments)
    );

    TWayGraph graph(1, 1);
    graph.Build(board, unit);
    std::string graphText = graph.ToString();
    auto ways = graph.FindWay(
        Coords::TColRowPoint(0, 0), 0,
        Coords::TColRowPoint(1, 2), 5
    );

    for (const auto& way : ways) {
        for (const auto& cmd : way) {
            std::cout << int(cmd) << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    try {
        //TestBuildGraph();
        TestFindWay();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
