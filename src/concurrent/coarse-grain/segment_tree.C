#include "segment_tree.H"
#include "benchmark.C"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <chrono>


// Helper functions

size_t next_pow_2(size_t v) {
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
void SegmentTree::update(size_t idx, int k) {
    m_data[idx] = (m_delta[idx] == 0)
        ? m_data[2*idx] + m_data[2*idx + 1]
        : k * m_delta[idx];
}

void SegmentTree::apply(size_t idx, int v, int k) {
    m_data[idx] = k * v;
    if (idx < m_cap)
        m_delta[idx] = v;
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
    for (l += m_cap, r += m_cap-1; lvl > 0; --lvl, k /= 2) {
        for (int i = l >> lvl; i <= static_cast<int>(r >> lvl); ++i) {
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

    pthread_mutex_lock(&mutex);
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
    pthread_mutex_unlock(&mutex);
}

int SegmentTree::range_sum(size_t l, size_t r) {
    pthread_mutex_lock(&mutex);
    push(l, l+1);
    push(r-1, r);

    int sum = 0;
    for (l += m_cap, r += m_cap; l < r; l /= 2, r /= 2) {
        if (l & 1)
            sum += m_data[l++];

        if (r & 1)
            sum += m_data[--r];
    }
    pthread_mutex_unlock(&mutex);
    return sum;
}

SegmentTree::SegmentTree(int *data, size_t len) {
    m_cap = next_pow_2(len);
    m_height = static_cast<size_t>(log(m_cap)) + 1;
    m_data = (int *)calloc(2*m_cap, sizeof(int));
    m_delta = (int *)calloc(m_cap, sizeof(int));
    pthread_mutex_init(&mutex, NULL);

    for (size_t i = 0; i < len; ++i)
        m_data[m_cap + i] = data[i];

    for (int i = m_cap - 1; i > 0; --i)
        m_data[i] = m_data[2*i] + m_data[2*i + 1];
    
    // printf("m_cap: %d\n", (int) m_cap);
    // printf("m_height: %d\n", (int) m_height);
    /*
    for (size_t i = 0; i <  2*m_cap; i++) {
        printf("%d ", m_data[i]);
    }
    printf("\n");
    */
}


int main() {
    /*
    std::cout << "tree.range_sum(0, 4): " << tree.range_sum(0, 4) << std::endl;
    std::cout << "tree.range_sum(0, 5): " << tree.range_sum(0, 5) << std::endl;
    std::cout << "tree.range_sum(2, 4): " << tree.range_sum(2, 4) << std::endl;

    std::cout << "tree.range_update(1, 4, 10)" << std::endl;
    tree.range_update(1, 4, 10);

    std::cout << "tree.range_sum(0, 5): " << tree.range_sum(0, 5) << std::endl;
    */
    using namespace std::chrono;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> dsec;
    srand(42);
    auto compute_start = Clock::now();
    double compute_time = 0;
    thread_sim();
    compute_time += duration_cast<dsec>(Clock::now() - compute_start).count();
    printf("Computation Time: %lf.\n", compute_time);
    /*
    update_heavy();
    compute_time += duration_cast<dsec>(Clock::now() - compute_start).count();
    printf("Update Heavy Computation Time: %lf.\n", compute_time);
    compute_start = Clock::now();
    compute_time = 0;
    sum_heavy();
    compute_time += duration_cast<dsec>(Clock::now() - compute_start).count();
    printf("Sum Heavy Computation Time: %lf.\n", compute_time);
    */
}
