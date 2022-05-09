#include <ctime>
#include <cstdlib>

#include "segment_tree.H"

#define COUNT 30000000

void update_heavy(void);

void sum_heavy(void);

void update_heavy() {
    size_t len = 1024 * 1024; // 4MB
    int *data = (int *) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++)
        data[i] = rand() % 100 + 1; // generate a number between 1 and 100
    SegmentTree tree(data, len);
    int l, r, v, n;
    for (int i = 0; i < COUNT; i++) {
        n = rand() % 100 + 1; // generate a number between 1 and 100
        if (n > 10) {
            // 90 percent chance of performing an update
            l = rand() % len + 1;
            r = rand() % len + 1;
            v = rand() % 100 + 1;
            tree.range_update(l, r, v);
        } else {
            l = rand() % len + 1;
            r = rand() % len + 1;
            tree.range_sum(l, r);
        }
    }
    free(data);
}

void sum_heavy() {
    size_t len = 1024 * 1024; // 4MB
    int *data = (int *) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++)
        data[i] = rand() % 100 + 1; // generate a number between 1 and 100
    SegmentTree tree(data, len);
    int l, r, v, n;
    for (int i = 0; i < COUNT; i++) {
        n = rand() % 100 + 1; // generate a number between 1 and 100
        if (n > 10) {
            // 90 percent chance of performing a sum
            l = rand() % len + 1;
            r = rand() % len + 1;
            tree.range_sum(l, r);
        } else {
            l = rand() % len + 1;
            r = rand() % len + 1;
            v = rand() % 100 + 1;
            tree.range_update(l, r, v);
        }
    }
    free(data);
}
