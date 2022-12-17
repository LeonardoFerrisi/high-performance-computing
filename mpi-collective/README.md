# MPI Collective

#### A Summary: 

| Vector Size     | Number of Processes | Time Elapsed (s) |     Improvement       |
|-----------------|:-------------------:|-----------------:|----------------------:|
|    480000000    |          1          |     9.156834     |        baseline       |
|    480000000    |          2          |     7.896937     |        1.259897       |
|    480000000    |          3          | SEMENTATIONFAULT |           NA          |
|    480000000    |          4          | SEMENTATIONFAULT |           NA          |


| Vector Size     | Number of Processes | Time Elapsed (s) |     Improvement       |
|-----------------|:-------------------:|-----------------:|----------------------:|
|    48000000     |          1          |     0.860943     |        baseline       |
|    48000000     |          2          |     0.757006     |          0.0039       |
|    48000000     |          3          |     0.717847     |          0.0448       |
|    48000000     |          4          |     0.673024     |         -0.1942       |
|    48000000     |          8          |     0.867176     |                  |


| Vector Size     | Number of Processes | Time Elapsed (s) |     Improvement       |
|-----------------|:-------------------:|-----------------:|----------------------:|
|    4800000      |          1          |     0.088547     |        baseline       |
|    4800000      |          2          |     0.071261     |           0.103       |
|    4800000      |          3          |     0.075080     |          -0.018  |
|    4800000      |          5          |     0.093503     |          0.0169  |
|    4800000      |          6          |     0.076627     |                  |


# =====================
# Revisions
# =====================

#### vector_normalization.c

- Previously, this file had a severe segmentation fault issue. After some copius amounts of debugging, I located the source as the MPI_Gather on line 159.
  After some research on the syntax for MPI_Gather, I narrowed the issue down to me gathering with a size specification of the full vectorSize rather than
  gathering myVectorSliceSize elements from each node. This fixed the issue there - however there was another bug
- The global magnitude had been (for debugging purposes) set to the square root of the first element of the global mag. It should have been set to the square root
  of the total sum which I adjusted allowing this code to truly normalize based off of an acutal global magnitude.
- VERBOSE is now a 0 or 1 argument which can be based in as a 3rd argument following arraySize and seed

- *IMPROVED TABLE*

| Vector Size     | Number of Processes | Time Elapsed (s) |         Speedup       |
|-----------------|:-------------------:|-----------------:|--------------------------:|
|    48000000     |          1          |     1.428672     |        baseline           | 
|    48000000     |          2          |     1.334880     |        1.07 or 7%         | (1.42../1.33..) 
|    48000000     |          3          |     1.294856     |        1.03 or 3%         | (1.33../ 1.29..)
|    48000000     |          4          |     1.317408     |        0.98 or -1.7%      | (1.29../ 1.31..)

#### MPI_Sort.c

- Previously, this file was unable to perform a standard sort due to some issues I was having with understanding the MPI_SendRecv function. The original file would always result in the programming hanging on a process that never finished. This was in part due to the error where I only called SendRecv on even nodes for the 'even' phase, this resulted in the odd nodes supposed to be involved in the process never being utilized. The updated code calls sendRecv in both odd and even nodes for both phases, but with properely adjusted parameter such that each node gets and gives the data they should during the appropriate phase.

# ======================
# Revision II
# ======================

## Additional tables for: MPI_Sort.c

| Vector Size     | Number of Processes | Time Elapsed (s) |         Speedup       |
|-----------------|:-------------------:|-----------------:|--------------------------:|
|    48000000     |          1          |     5.207705     |        baseline           | 
|    48000000     |          2          |     2.867772     |        1.82 or 82%         | (5.21../2.86..) 
|    48000000     |          3          |     2.423835     |        1.18 or 18%         | (2.87../ 2.42..)
|    48000000     |          4          |     2.058654     |        1.17 or 17%      | (2.42../ 2.06..)

| Vector Size     | Number of Processes | Time Elapsed (s) |         Speedup       |
|-----------------|:-------------------:|-----------------:|--------------------------:|
|    64000000     |          1          |     7.199282     |        baseline           | 
|    64000000     |          2          |     3.914935     |        1.84 or 84%         | (7.20../3.91..) 
|    64000000     |          4          |     2.544084     |        1.54 or 54%      | (7.20../ 2.54..)

| Vector Size     | Number of Processes | Time Elapsed (s) |         Speedup       |
|-----------------|:-------------------:|-----------------:|--------------------------:|
|    148000000     |          1          |     16.802135    |        baseline           | 
|    148000000     |          2          |     9.284435     |        1.81 or 81%         | (16.80../9.28..) 
|    148000000     |          4          |     5.798738     |        1.60 or 60%      | (9.28../ 5.80..)
