#include <cmath>
#include <cstdlib>

#include "segment_tree.H"

// Helper functions

inline size_t next_pow_2(size_t v) {
    --v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    return v + 1;
}

// Class functions
inline void SegmentTree::apply(size_t idx, int v, int k) {
    m_data[idx] = k * v;
    if (idx < m_cap)
        m_delta[idx] = v;
}

inline void SegmentTree::update(size_t idx, int k) {
    m_data[idx] = (m_delta[idx] == 0)
        ? m_data[2*idx] + m_data[2*idx + 1]
        : k * m_delta[idx];
}

void SegmentTree::build(size_t l, size_t r) {
    int k = 2;
    for (l += m_cap, r += m_cap-1; l > 1; k *= 2) {
        l /= 2;
        r /= 2;
        for (size_t i = r; i >= l; --i)
            update(i, k);
    }
}

void SegmentTree::push(size_t l, size_t r) {
    int lvl = m_height;
    int k = 1 << (lvl-1);
    int i;

    for (l += m_cap, r += m_cap-1; lvl > 0; --lvl, k /= 2) {
#pragma omp for
        for (i = l >> lvl; i <= static_cast<int>(r >> lvl); ++i) {
            if (m_delta[i] != 0) {
                apply(2*i, m_delta[i], k);
                apply(2*i + 1, m_delta[i], k);
                m_delta[i] = 0;
            }
        }
    }
}

void SegmentTree::range_update(size_t l, size_t r, int v) {
    if (v == 0)
        return;

    push(l, l+1);
    push(r-1, r);

    int l_copy = l, r_copy = r;
    int k = 1;
    for (l += m_cap, r += m_cap; l < r; l /= 2, r /= 2, k *= 2) {
        if (l & 1)
            apply(l++, v, k);

        if (r & 1)
            apply(--r, v, k);
    }

    build(l_copy, l_copy+1);
    build(r_copy-1, r_copy);
}

int SegmentTree::range_sum(size_t l, size_t r) {
    push(l, l+1);
    push(r-1, r);

    int sum = 0;
    for (l += m_cap, r += m_cap; l < r; l /= 2, r /= 2) {
        if (l & 1)
            sum += m_data[l++];

        if (r & 1)
            sum += m_data[--r];
    }
    return sum;
}

SegmentTree::SegmentTree(int *data, size_t len) {
    m_cap = next_pow_2(len);
    m_height = static_cast<size_t>(log(m_cap)) + 1;
    m_data = (int *)calloc(2*m_cap, sizeof(int));
    m_delta = (int *)calloc(m_cap, sizeof(int));

    for (size_t i = 0; i < len; ++i)
        m_data[m_cap + i] = data[i];

    for (int i = m_cap - 1; i > 0; --i)
        m_data[i] = m_data[2*i] + m_data[2*i + 1];
}
