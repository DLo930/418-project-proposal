#pragma once
#include <cstddef>

class SegmentTree {
    int *m_data;
    int *m_delta;
    size_t m_cap;
    size_t m_height;

    void apply(size_t idx, int v, int k);
    void update(size_t idx, int k);
    void build(size_t l, size_t r);

public:
    void range_update(size_t l, size_t r, int v);
    int range_sum(size_t l, size_t r);

    SegmentTree(int *data, size_t len);
};
