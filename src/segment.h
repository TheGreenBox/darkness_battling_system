class TSegment {
public:
    TSegment(size_t row, size_t column);

    TSegment Move(EMoveOperations direction) const;

private:
    size_t Row;
    size_t Column;
};
