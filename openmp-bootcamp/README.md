# OpenMP


## pfor-no-sugar-arraysum.c

| nThreads | time elapsed (ms) | speedup |
|----------|-------------------|---------|
|    1     |     0.008837      | Baseline|
|    2     |     0.144316      |   0.061 or -93%      |
|    3     |     0.228811      |   0.631 or -37% |
|    4     |     0.231663      |   0.979 or -2%      |


## omp-pi.c 


|  N        | nThreads | time elapsed (s) | speedup |
|-----------|----------|-------------------|---------|
| 100000000 |    1     |     1.134811      | Baseline|
| 100000000 |    2     |     0.580972      |   1.95 or 95%      |
| 100000000 |    3     |     0.386024      |   1.51 or 51% |
| 100000000 |    4     |     0.298986      |   1.29 or 29%      |

|  N        | nThreads | time elapsed (s) | speedup |
|-----------|----------|-------------------|---------|
| 400000000 |    1     |     4.551674      | Baseline|
| 400000000 |    2     |     2.310771      |   1.97 or 97%      |
| 400000000 |    3     |     1.545190      |   1.50 or 50% |
| 400000000 |    4     |     1.187631      |   1.30 or 30%      |

|  N        | nThreads | time elapsed (s) | speedup |
|-----------|----------|-------------------|---------|
| 999999999 |    1     |     11.47693      | Baseline|
| 999999999 |    2     |     5.761613      |   1.99 or 99%      |
| 999999999 |    3     |     3.849415      |   1.50 or 50% |
| 999999999 |    4     |     2.947402      |   1.31 or 30%      |

# Revisions:

## Analysis

As demonstrated through the pfor-no-sugar-arraysum project with arrays of incredibly small, the benefit of adding extra cores is non existent.
In contrast - the file omp-pi.c, consistently provided the same speedups with increasing number of threads for larger arrays.

For both of these parallelized programs, as exected the speedups decrease with increasing number of threads. As we add more threads, more time is spent simply getting the data to be handled by different cores resulting in some extra time taken before the threads can actually be completed.

The declining speedups or rather, lack of linear speedup is a clear example of Amdahl's law in practice - with diminishing returns in terms of speedup.

In contrast, the pfor-no-sugar-arraysum has slowdowns with increasing number of threads. Because the array is so small, the benefit of parallelizing it is overshadowed by the time cost of sharing memory. Only with larger arrays would the benefit be enough to actually result in speedups.

Also, as shown with the omp-pi.c in comparsion to pfor-no-sugar, using the reduction clause in the omp statement significantly helped timing for arrays of several different massive sizes with consistent speedups even with up to 4 threads.
