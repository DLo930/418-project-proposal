#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct {
    int id;
    SegmentTree *tree;
} input_t;

void update_heavy(void);

void sum_heavy(void);

void *thread(void *vargp);

void thread_sim(void);

void update_heavy() {
    size_t len = 1024 * 1024; // 4MB
    int *data = (int *) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++)
        data[i] = rand() % 100 + 1; // generate a number between 1 and 100
    SegmentTree tree(data, len);
    int count = 100000000;
    int l, r, v, n;
    for (int i = 0; i < count; i++) {
        n = rand() % 100 + 1; // generate a number between 1 and 100
        if (n > 10) {
            // 90 percent chance of performing an update
            l = rand() % len + 1;
            r = rand() % len + 1;
            if (l >= r) {
                l = r / 2;
            }
            v = rand() % 100 + 1;
            tree.range_update(l, r, v);
        } else {
            l = rand() % len + 1;
            r = rand() % len + 1;
            if (l >= r) {
                l = r / 2;
            }
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
    int count = 30000000;
    int l, r, v, n;
    for (int i = 0; i < count; i++) {
        n = rand() % 100 + 1; // generate a number between 1 and 100
        if (n > 10) {
            // 90 percent chance of performing a sum
            l = rand() % len + 1;
            r = rand() % len + 1;
            if (l >= r) {
                l = r / 2;
            }
            tree.range_sum(l, r);
        } else {
            l = rand() % len + 1;
            r = rand() % len + 1;
            v = rand() % 100 + 1;
            if (l >= r) {
                l = r / 2;
            }
            tree.range_update(l, r, v);
        }
    }
    free(data);
}

void *thread(void *vargp) {
    int id = ((input_t *) vargp)->id;
    SegmentTree *tree = ((input_t *) vargp)->tree;
    int count = 10;
    int push_count = 10;
    size_t len = 1024 * 1024;
    int l, r, v;

    if (id == 0) { // producer
        for (int i = 0; i < push_count; i++) {
            l = rand() % len + 1;
            r = rand() % len + 1;
            v = rand() % 100 + 1;
            if (l >= r) {
                l = r / 2;
            }
            tree->range_update(l, r, v);
        }
    } else {
        for (int i = 0; i < count; i++) {
            l = rand() % len + 1;
            r = rand() % len + 1;
            if (l >= r) {
                l = r / 2;
            }
            tree->range_sum(l, r);
        }
    }
    free(vargp);
    return NULL;
}

void thread_sim() {
    size_t len = 1024 * 1024 * 2; // 4MB
    int *data = (int *) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++)
        data[i] = rand() % 100 + 1; // generate a number between 1 and 100

    SegmentTree tree(data, len);
    int num_threads = 32000;
    pthread_t tid[num_threads];
    input_t *input;
    for (int i = 0; i < num_threads; i++) {
        input = (input_t *) malloc(sizeof(input_t));
        input->id = i;
        input->tree = &tree;
        pthread_create(&tid[i], NULL, thread, (void *) input);
    }
    for (int i = 0; i < num_threads; i++) {
       pthread_join(tid[i], NULL);
    }

    free(data);
}
