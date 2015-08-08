#pragma once

#include <vector>

class TBoard {
public:
    TBoard(size_t rows, size_t columns);

    void LockSegment(size_t row, size_t column);
    void UnlockSegment(size_t row, size_t column);

    bool SegmentIsLocked(size_t row, size_t column) const;

private:
    using TRow = std::vector<bool>;
    using TSegments = std::vector<TRow>;

    static bool IS_LOCKED;
    static bool IS_UNLOCKED;

    void SetSegmentStatus(size_t row, size_t column, bool newStatus);

    TSegments SegmentsStatuses;
};
