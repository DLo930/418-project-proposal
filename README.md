- BACKGROUND: If your project involves accelerating a compute-intensive application, describe the application or piece of the application you are going to implement in more detail. This description need only be a few paragraphs. It might be helpful to include a block diagram or pseudocode of the basic idea. An important detail is what aspects of the problem might benefit from parallelism and why?
- THE CHALLENGE: Describe why the problem is challenging. What aspects of the problem might make it difficult to parallelize? In other words, what to you hope to learn by doing the project?
Describe the workload: what are the dependencies, what are its memory access characteristics? (is there locality? is there a high communication to computation ratio?), is there divergent execution?
Describe constraints: What are the properties of the system that make mapping the workload to it challenging?
- RESOURCES: Describe the resources (type of computers, starter code, etc.) you will use. What code base will you start from? Are you starting from scratch or using an existing piece of code? Is there a book or paper that you are using as a reference (if so, provide a citation)? Are there any other resources you need, but havenâ€™t figured out how to obtain yet? Could you benefit from access to any special machines?
- GOALS AND DELIVERABLES: Describe the deliverables or goals of your project. This is by far the most important section of the proposal!
Separate your goals into what you PLAN TO ACHIEVE ("100%" -- what you believe you must get done to have a successful project and get the grade you expect) and an extra goal or two ("125%") that you HOPE TO ACHIEVE if the project goes really well and you get ahead of schedule, as well as goals in case the work goes more slowly ("75%"). It may not be possible to state precise performance goals at this time, but we encourage you be as precise as possible. If you do state a goal, give some justification of why you think you can achieve it. (e.g., I hope to speed up my starter code 10x, because if I did it would run in real-time.)
If applicable, describe the demo you plan to show at the poster session (Will it be an interactive demo? Will you show an output of the program that is really neat? Will you show speedup graphs?). Specifically, what will you show us that will demonstrate you did a good job?
If your project is an analysis project, what are you hoping to learn about the workload or system being studied? What question(s) do you plan to answer in your analysis?
Systems project proposals should describe what the system will be capable of and what performance is hoped to be achieved.
- PLATFORM CHOICE: Describe why the platform (computer and/or language) you have chosen is a good one for your needs. Why does it make sense to use this parallel system for the workload you have chosen?
- SCHEDULE: Produce a schedule for your project. Your schedule should have at least one item to do per week. List what you plan to get done each week from now until the parallelism competition in order to meet your project goals. Keep in mind that due to other classes, youâ€™ll have more time to work some weeks than others (work that into the schedule). You will need to re-evaluate your progress at the end of each week and update this schedule accordingly. Note the intermediate checkpoint deadline is April 11th. In your schedule we encourage you to be precise as precise as possible. Itâ€™s often helpful to work backward in time from your deliverables and goals, writing down all the little things youâ€™ll need to do (establish the dependencies).

# Lock-free and Concurrent Lazy Segment Tree
Dennis Lo, Shize Che

## Summary
Segment queries are pervasive in computational geometry and other problem spaces. To address this important use case, we are going to implement an optimized lazy segment tree implementation to support fast range read and write queries on large datasets.

## Background
It is a very common use case in computational geometry to calculate shape overlap, such as with rectangles in the 2D Euclidean space. 

Segment queries typically involve the following operations over a fixed-size array of primitive data:
```
void update(size_t pos, int v);
void range_update(size_t start_pos, size_t end_pos, int v);
int range_sum(size_t start_pos, size_t end_pos);
```
A concurrent segment tree can be implemented using locks and atomics to ensure that queries over disjoint ranges can occur in parallel. Another potential area of parallelization lies in the two range operations in which we can divide the range over which values are read or updated across workers. These two are eligible for parallelization because there are no data dependencies between non-overlapping subtrees.

## The Challenge
Implementing concurrent data structures poses a fundamental challenge of allowing progress on multiple threads while maintaining some form of correctness. It is also difficult to incorporate lock-freeness in most data structures since the implementer is limited to a set of intrinsics and primitives and must be very careful about the potential race conditions that may result. Through undertaking this project, we hope to gain experience reasoning about the nuances of lock-free and concurrent data structures as well as programming for high performance on specific hardware.

## Resources
We will start the implementation from scratch and follow the paper ("Parallel Range, Segment and Rectangle Queries with Augmented Maps")[https://www.cs.cmu.edu/~yihans/papers/geometry.pdf] and ("Implementing Parallel and Concurrent Tree Structures")[https://www.cs.cmu.edu/~yihans/papers/tutorial.pdf] as a reference. We plan on benchmarking our implementation with MPI, ISPC, and pthreads to benchmark our implementation. The benchmarks will be performed on CMU's GHC cluster.

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
