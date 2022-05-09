#include <iostream>
#include <ctime>
#include <chrono>

#include "benchmark.C"
#include "segment_tree.H"

int main() {
    // int data[] = { 3, 6, 2, -1, 4 };
    // SegmentTree tree(data, 5);

    // std::cout << "tree.range_sum(0, 4): " << tree.range_sum(0, 4) << std::endl;
    // std::cout << "tree.range_sum(0, 5): " << tree.range_sum(0, 5) << std::endl;
    // std::cout << "tree.range_sum(2, 4): " << tree.range_sum(2, 4) << std::endl;

    // std::cout << "tree.range_update(1, 4, 10)" << std::endl;
    // tree.range_update(1, 4, 10);

    // std::cout << "tree.range_sum(0, 5): " << tree.range_sum(0, 5) << std::endl;
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
