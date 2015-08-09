#pragma once

#include "coordinate_systems.h"
#include "segment.h"
#include "unit.h"
#include "board.h"

#include <array>
#include <cstddef>
#include <vector>
#include <string>

class TWayGraph {
public:
    using Coordinate = Coords::ColRowPoint::Coordinate;

    explicit TWayGraph(Coordinate rowShift, Coordinate columnShift);
    TWayGraph(const TWayGraph&) = delete;

    void Build(const TBoard&, const TUnit&);

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

    TWayGraph Clone() const;

    std::vector<EMoveOperations>
    FindWay(
        const TSegment& from,
        const TSegment& to
    );

private:
    static const size_t TurnDirections = 6;
    using TVertical = std::array<TNode, TurnDirections>;
    using TMatrixRow = std::vector<TVertical>;
    using TMatrix = std::vector<TMatrixRow>;

    TSegment GetCoordinateFromIndex(size_t column, size_t row);

    size_t GetRowIndexFromCoordinate(Coordinate row);

    size_t GetColumnIndexFromCoordinate(Coordinate column);

    TMatrix Graph;
    Coords::ColRowPoint::Coordinate RowShift;
    Coords::ColRowPoint::Coordinate ColumnShift;
};

