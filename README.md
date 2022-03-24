# Lock-free and Concurrent Segment Tree
Dennis Lo, Shize Che

## Summary
Segment queries are pervasive in computational geometry and other problem spaces. To address these important use cases, we are going to implement an optimized lazy segment tree implementation to support fast range read and write queries on large datasets.

## Background
It is a common use case in computational geometry to calculate shape overlap, such as with rectangles in the 2D Euclidean space.

Segment queries typically involve the following operations over a fixed-size array of primitive data:
```
void update(size_t pos, int v);
void range_update(size_t start_pos, size_t end_pos, int v);
int range_sum(size_t start_pos, size_t end_pos);
```
A concurrent segment tree can be implemented using locks and atomics to ensure that queries over disjoint ranges can occur in parallel. Another potential area of parallelization lies in the two range operations in which we can divide the range over which values are read or updated across workers. These two are eligible for parallelization because there are no data dependencies between non-overlapping subtrees. With a sufficiently large dataset, a parallel implementation could offer a considerable speedup over the sequential baseline implementation, particularly in the presence of multiple consumers.

## The Challenge
Implementing concurrent data structures poses a fundamental challenge of allowing progress on multiple threads while maintaining some form of correctness. It is also difficult to incorporate lock-freeness in most data structures since the implementer is limited to a set of intrinsics and primitives and must be very careful about the potential race conditions that may result. Through undertaking this project, we hope to gain experience reasoning about the nuances of lock-free and concurrent data structures as well as programming for high performance on specific hardware.

## Resources
We will start the implementation from scratch and follow the papers ["Parallel Range, Segment and Rectangle Queries with Augmented Maps"](https://www.cs.cmu.edu/~yihans/papers/geometry.pdf) and ["Implementing Parallel and Concurrent Tree Structures"](https://www.cs.cmu.edu/~yihans/papers/tutorial.pdf) for reference. We plan on benchmarking our implementation with MPI, ISPC, and pthreads to benchmark our implementation. The benchmarks will be performed on CMU's GHC cluster.

## Goals & Deliverables
- Do background research on current solutions to range queries
- Implement baseline sequential lazy segment tree
- Design experimental segment tree (diagrams of logic flow of parallelized and critical sections)
- Implement ISPC (75%), pthreads (100%), and MPI (125%) versions of the segment tree and ensure expected behavior
- Generate workloads for testing and benchmarking
- Perform benchmarks on GHC machines

## Schedule
- 3/24 - 3/27: Do preliminary research on existing designs/solutions
- 3/28 - 3/30: Implement baseline tree
- 3/31 - 4/4: Design experimental tree
- 4/5 - 4/8: Implement ISPC version of tree
- 4/9 - 4/10: Benchmark baseline and experimental, generate speedup graphs
- 4/11 - Checkpoint
- 4/11 - 4/15: Implement pthreads and MPI versions
- 4/16 - 4/18: Benchmark all implementations
- 4/19 - 4/24: Optimize implementations
- 4/25 - 4/28: Prepare final report
- 4/29: Submit report by midnight
- 4/30 - 5/4: Prepare final board presentation
- 5/5: Final presentation
