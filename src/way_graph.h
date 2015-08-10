#pragma once

#include "board.h"
#include "coordinate_systems.h"
#include "segment.h"
#include "unit.h"

#include <array>
#include <cstddef>
#include <limits>
#include <string>
#include <vector>
#include <queue>

class TWayGraph {
public:
    using TCoordinate = Coords::TColRowPoint::TCoordinate;

    TWayGraph(TCoordinate rowShift, TCoordinate columnShift);

    TWayGraph(TWayGraph&&) = default;
    TWayGraph& operator=(TWayGraph&&) = default;

    TWayGraph() = delete;
    TWayGraph(const TWayGraph&) = delete;
    TWayGraph& operator=(const TWayGraph&) = delete;

    void Build(const TBoard&, const TUnit&);

    TWayGraph Clone() const;

    using TWay = std::vector<EMoveOperations>;
    using TWays = std::vector<TWay>;

    struct TEndPosition {
        TEndPosition()
            : Unit(TUnit(
                TSegment(Coords::TColRowPoint(0, 0)),
                TUnit::TSegments()
            ))
        {
        }
        int Metrics;
        TUnit Unit;
        size_t Direction;
        bool operator<(const TEndPosition& other) const {
            return Metrics < other.Metrics;
        }
    };
    std::priority_queue<TEndPosition>
    FindPositionWithMaxMetrics(const TUnit& unit, size_t fromDirection);

    TWays
    FindWay(
        const Coords::TColRowPoint& from,
        size_t fromDirection,
        const Coords::TColRowPoint& to,
        size_t toDirection
    );

    bool
    CheckNode(
        TCoordinate column,
        TCoordinate row,
        size_t direction
    ) const;

    std::string ToString() const;

private:
    enum class EColor {
        WHITE,
        GREY,
        BLACK
    };

    struct TNode {
        int Metrics = std::numeric_limits<int>::min();
        EColor Color = EColor::WHITE;  // for dfs algo
        bool Available = false;
    };

    static const size_t TurnDirections = 6;
    using TVertical = std::array<TNode, TurnDirections>;
    using TMatrixRow = std::vector<TVertical>;
    using TMatrix = std::vector<TMatrixRow>;

    Coords::TColRowPoint
    GetCoordinateFromIndex(
        size_t colInd, size_t rowInd
    ) const;

    size_t GetRowIndexFromCoordinate(TCoordinate row) const;

    size_t GetColumnIndexFromCoordinate(TCoordinate column) const;

    void Dfs(const TSegment& point, size_t direction);

    TNode&
    GetNode(
        TCoordinate column,
        TCoordinate row,
        size_t direction
    );

    const TNode&
    GetNode(
        TCoordinate column,
        TCoordinate row,
        size_t direction
    ) const;

    TMatrix Graph;

    Coords::TColRowPoint::TCoordinate RowShift;
    Coords::TColRowPoint::TCoordinate ColumnShift;

    TWays AllWays;
    TWay CurrentWay;
    TSegment FinishPoint;
    size_t FinishDirection;

    bool IsValid(const Coords::TColRowPoint&) const;

    bool IsCollision(
        const TSegment& point,
        size_t direction
    ) const;

    EMoveOperations FindCollisionDirection(
        const TSegment& point,
        size_t direction
    ) const;
};

