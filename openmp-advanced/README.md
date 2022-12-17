# OpenMP Advanced


## Matrix Addition

### Parallel Matrix Addition - 100 x 100

*Where Static and Dynamic are refering to time in (ms) under each condition*

|nthreads|   Static Speedup   |  Dynamic Speedup   |Static (c=100) | Dynamic (c=100)|
|--------|--------------------|--------------------|---------------|----------------|
|   1    |                    |                    |0.032808       |   0.190012     |
|   2    |0.2737718735        |1.117448145         |0.119837       |   0.170041     |
|   4    |1.312634865         |0.4028806126        |0.091295       |    0.422063    |
|   8    |0.3515456534        |0.6682250981        |0.259696       |   0.631618     |
|   12   |1.164582166         |1.254566942         |0.222995       |   0.503455     |

### Parallel Matrix Addition - 500 x 500

*Where Static and Dynamic are refering to time in (ms) under each condition*

|nthreads|   Static Speedup   |  Dynamic Speedup   |Static (c=100) | Dynamic (c=100)|
|--------|--------------------|--------------------|---------------|----------------|
|   1    |                    |                    |1.465605       |   1.31169     |
|   2    |0.3766566976        |0.3838216347        |0.921279       |   3.482455    |
|   4    |1.438271412         |5.188517324         |0.640546       |   0.671185    |
|   8    |0.1669505883        |0.7575365967        |3.83674        |   0.88601     |
|   12   |1.221226268         |0.7442941592        |3.141711       |   1.190403    |

### Parallel Matrix Addition - 2000 x 2000

*Where Static and Dynamic are refering to time in (ms) under each condition*

|nthreads|   Static Speedup   |  Dynamic Speedup   |Static (c=100) | Dynamic (c=100)|
|--------|--------------------|--------------------|---------------|----------------|
|   1    |                    |                    |20.592375      |   20.763405    |
|   2    |1.909488181         |1.918641237         |10.784238      |   10.821932    |
|   4    |1.486262368         |1.816806286         |7.255945       |   5.956569     |
|   8    |1.027514544         |0.9269118298        |7.061647       |   6.426252     |
|   12   |0.9797891392        |1.043664929         |7.207313       |   6.15739      |

## Matrix Transposition

### Parallel Matrix Transposition - 100 x 100

*Where Static and Dynamic are refering to time in (ms) under each condition*

|nthreads|   Static Speedup   |  Dynamic Speedup   |Static (c=100) | Dynamic (c=100)|
|--------|--------------------|--------------------|---------------|----------------|
|   1    |                    |                    |0.123314       |   0.091433    |
|   2    |1.502455072	      |0.3803670007        |0.082075       |   0.240381    |
|   4    |1.242533554         |0.1523114161        |0.099244       |   0.600303    |
|   8    |0.5489160917        |0.2447160151        |0.22465        |   0.373629    |
|   12   |0.3685107044        |0.126915891         |0.334628       |   0.720422    |


### Parallel Matrix Transposition - 500 x 500

*Where Static and Dynamic are refering to time in (ms) under each condition*

|nthreads|   Static Speedup   |  Dynamic Speedup   |Static (c=100) | Dynamic (c=100)|
|--------|--------------------|--------------------|---------------|----------------|
|   1    |                    |                    |2.514755       |   1.149337     |
|   2    |2.062036868	      |1.077031563         |1.219549       |   1.067134     |
|   4    |0.3188053345        |0.9164912498        |3.825372       |   1.164369     |
|   8    |3.227257848         |1.038943576         |1.185332       |   1.120724     |
|   12   |0.9961032598        |0.9690292536        |1.189969       |   1.156543     |


### Parallel Matrix Transposition - 2000 x 2000

*Where Static and Dynamic are refering to time in (ms) under each condition*

|nthreads|   Static Speedup   |  Dynamic Speedup   |Static (c=100) | Dynamic (c=100)|
|--------|--------------------|--------------------|---------------|----------------|
|   1    |                    |                    |27.087852      |   27.358868    |
|   2    |1.673034274         |1.754280982         |16.190853      |   15.595488    |
|   4    |0.915171186         |1.525631569         |17.7           |   10.222316    |
|   8    |1.436733209         |1.012532606         |12.319615      |   10.096623    |
|   12   |1.021491502         |0.991229593         |10.943821      |   10.185958    |

# Revsions:

## Analysis:

For almost every operation with an increasing number of threads, the omp dynamic parallel for loops performed better in terms of timing and performed around the same as static parallel for in terms of speedup. Dyanmic is an excellent way to conduct processes in parallel if some of them take variable amounts of time to complete - and while the speedups are not substantially greater than the static when the threads increase, we can clearly see that the Dynamic parallel for loops take less time than the static ones to complete. After around 4 threads, the benefit of adding more threads begins to decline resulting in the eventual slowdown from 8 threads to 12 threads.

The static scheduling has speedups which are somewhat inconsistent as threads increase. The static parallel for shows regular speedups from 4 to 8 threads, but a slowdown from 2 to 4. With smaller matricies it shows consistent slowdowns as threads increase for both matrix addition and matrix transposition. As shown in the collective matrix timing data google sheets (https://docs.google.com/spreadsheets/d/1VLiPnbb17uWstqTzG07fMQ_N8GsqTXyl4D-6zgoVg4E/edit#gid=74116286), there are diminishing returns for both dynamic and static scheduling of omp for loops.

As according to Amdahls law, the benefit of parallelizing a serial program decreases with the number of processes - however we are able to make the best of it by using dynamic scheduling such that we can run everything as soon as something is the previous amount of data is done running. 

Another option could have been to use something such as guided schedules so as to allow for variable chunk sizes as the program completes.


