# MPI Advanced


## Vector Mean

##### When factoring in vector generation when num_process = number of vectors generated

|  Vector Size  | Num Processes | Time Elapsed (s) |   Speedup      |                  |
|---------------|---------------|-------------------|----------------|-----------------|
|   480000000   |       1       |     9.035806      |    Baseline    |                 |
|   480000000   |       2       |     4.598746      |   1.96 or 96%  | (9.03../4.59..) |
|   480000000   |       3       |     3.068941      |   1.50 or 50%  | (4.59../3.07..) |
|   480000000   |       4       |     2.369752      |   1.30 or 30%  | (3.07../2.37..) |


|  Vector Size  | Num Processes | Time Elapsed (s) |   Speedup        |                    |
|---------------|---------------|-------------------|-----------------|--------------------|
|   1920000000   |       1       |     36.12746      |    Baseline    |                    |
|   1920000000   |       2       |     18.21056      |   1.98 or 98%  | (36.13../18.21..)  |
|   1920000000   |       3       |     12.30774      |   1.48 or 48%  | (18.21s../12.31..) |
|   1920000000   |       4       |     9.740952      |   1.26 or 26%  | (12.31../9.74..)   |


## Vector Standard Deviation


|  Vector Size  | Num Processes | Time Elapsed (ms) |   Speedup       |                  |
|---------------|---------------|-------------------|-----------------|------------------|
|   20000000     |       1       |     59.54455      |    Baseline    |                  |
|   20000000     |       2       |     30.79481      |   1.93 or 93%  | (59.54../30.79..)|
|   20000000     |       4       |     17.73961      |   1.74 or 74%  | (30.79../17.74..)|


|  Vector Size  | Num Processes | Time Elapsed (ms) |   Speedup       |                        |
|---------------|---------------|-------------------|-----------------|------------------------|
|   600000000    |       1       |     1643.055      |    Baseline    |                        |
|   600000000    |       2       |     879.8509      |   1.87 or 87%  | (1643.055../879.8509..)|
|   600000000    |       4       |     521.3545      |   1.69 or 69%  | (879.8509../521.3545..)|
