# <center>Week 2 Assignments</center>

# Tasks 

- [ x ] Array Sum 
- [ x ] Vector Dot
- [ x ] Vector Add 

# Observations and Measures

### Array Sum

###### The algrothim to run a Block Based array sum is simple:
- Take the size of the Array and divide it by the number of processes. This is your block size
- To get the remainder, if there is one, do <Array Size> mod <Number of processes>
- Define two variables indicating where to start and end
    - Where to start is easy, its the product of which process you are times the block size
    - Where to end is just the sum of your start point and the block size
        - If the process you are running is the last one, have a statement that adds the remainder amount of indicies to the end point
- Create a for loop that iterates through the start index to the end index for each process
- Your result should be 1057, just like the cyclic assignment did

### Vector Dot Product
- The speed of a program strangley does not increase with the number of processes/processors
- The speed does however increase with increasing sizes of vectors
    - For example: 
    - A vector of size 2000 takes roughly 30 ms
    - Whereas a vector of size 2000000 takes roughly 260 ms

# Results

#### Array Sum


| Num Processes |  Time Elapsed (ms)  | Improvement     |
|---------------|--------------------|-----------------|
|      1        |       0.001669     | baseline        |
|      2        |       0.008345     |   0.2 (0.001669/0.008345)        |
|      3        |       1.669645     |   0.005       |
|      4        |       0.332117     |   5.027        |

#### Vector Dot Product

*With seed 1234*

|   Size   | Num Processes |  Time Elapsed (ms) | Improvement     |
|----------|---------------|--------------------|-----------------|
|     10   |       1       |       0.033140     |     baseline |
|     10   |       2        |    0.057459       |     0.59   (0.033140/0.057459)       |
|     10   |       3        |      0.343084     |       0.16          | 
|     10   |       4        |   0.123978        |       2.77        | 
|   100000   |        1       |         0.359535           |         baseline        |  
|   100000   |        2       |         0.914335           |         0.39        |  
|   100000   |        3       |         1.508713           |         0.61        |  
|   100000   |        4       |         1.724958           |        0.87        |  
|100000000 |       1       |      332.280397    |      baseline        |  
|100000000 |       2       |      1089.288473    |      0.31        |  
|100000000 |       3       |      1669.414282    |       0.65       |  
|100000000 |       4       |      2348.495483    |      0.71       |  

#### Vector Add (Challenge)

*With seed 1234*


|   Size   | Num Processes |  Time Elapsed (ms) | Improvement     |
|----------|---------------|--------------------|-----------------|
|   100000   |        1       |         0.379324           |         baseline        |  
|   100000   |        2       |         1.843929           |         0.20        |  
|   100000   |        3       |         2.018213           |         0.91        |  
|   100000   |        4       |         1.927614           |        1.05        |  
|100000000 |       1       |      334.528685    |      baseline        |  
|100000000 |       2       |      1743.538380    |      0.19        |  
|100000000 |       3       |      17435.001373    |       0.10       | 
|100000000 |       4       |      22422.565699    |      0.77       |  
