<center>Leonardo Ferrisi</center>

# Task List
- [X] Factorization
- [X] Vectors and Pointers
- [X] Linked List in C

# Assignment 1

### Initial change (Step 3): 
- break removed, iterates up to number value
- prints if number is prime
- A number like 3,000,000 takes roughly 19.5 ms to run, 95 divisors are found, is not prime

**times = (19.500420, 23.257700, 19.244500, 19.524000)**

- A number like 3,456,789,101 takes roughly 19060 ms to run (around 19 seconds), 2 divisors are found, is not prime

**times = (19060, 13733)**


### Secondary change (Step 4):
- for loop increments by two instead of 1 now
- loop breaks if a square root is found

- A number like 99980001 takes roughly 0.233 ms before a square root of 9999 is reached. 22 divisors are found, is not prime

- A number like 15241383936 takes roughly 60658 ms to run, (roughly 60 seconds) and does have a square root but this square root is even, so it is never hit - 8 divisors are found, is not prime

- A number like 3890609 takes roughly 20.61 ms to run. it does have a square root but square root not a whole number thus is never reached. 0 divisors are found, is prime

**times = (20.61, 20.78, 24.11, 23.73, 21.71, 22.27)**


|  number |    time elapsed  (ms)   |     num divisors     |
|--------|---------|----------|
|    20    |     0.076000    |     2     |
|   28409    |     0.173000    |     0     |
|    7238    |     0.105000    |     7     |
|    217351    |     0.882000    |      0    |
|    2162351    |     7.849000    |      0    |
|    21623581    |     77.625000    |      2    |


# Assignment 2

##### (Step 4):
    - When adding a larger size than the actual size of the vector the randomizer gets random doubles as many times as the input size, but the
        print_vector functions still print out the SIZE amount... unless they 
        are given a larger parameter too, in which case it begins giving the values of the next vector
    - It must be accessing the memory addresses of the next vector since it thinks the size of itself is larger!
    - If the calloc sizes are the same as SIZE, but the randomize is larger, it begins randomizing in the area of memory associated with the next vector (of course when the randomize vector is called for the next vector, those locations are randomized again)

##### (Step 7):
    - Increasing the size by 10 times
    - Up until 10^6 time in ms is still under 100ms runtime
    - At 10^7 runtime is 384 ms
    - At 10^8 runtime is 3847 ms
    - At 10^9 runtime runs for a while and then shows the message 'killed'

*timing, using seed of 1234* 

**For two vectors, using four took an eternity?**

|     vector size      |     time (ms)       |
|-----------|------------|
|    10^2      |      1.093000      |
|    10^5      |      1114.095000      |
|    10^6      |      10013.476000      |
|    10^7      |      12326.159000      |

# Assignment 3

##### (Step 2):
    - The algorithm for a recursive print is pretty simple:
    1. print the data of the current node
    2. If the next node is not NULL, PrintList that node
    3. If the next node *is* NULL, print '->NULL'
    - Works great... yay!

##### (Step 3):
    - The algorithm for a recursive insert is pretty easy too:
    > We want to insert the integer such that every node before it is less than its value and every node after greater
    1. If the current list pointer is NULL or the int 'N' is less than the list pointer:
    - Insert the integer and make it's next value equal to the original value for this list pointer
    2. Otherwise, make the next value for this list pointer equal to the result of insertRecursive for the next value of this list pointer
    - Works great.. hurrah!
