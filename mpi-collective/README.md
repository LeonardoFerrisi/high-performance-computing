# <center> Week 3 Assignments</center>

# Hands-On: Vector Normalization

### Targets

- [ ] CP.1	C Programming (editing, compiling)
- [ ] CP.2	C Debugging (your code, other's code)
- [ ] PP.3	Parallelization of Serial Programs
- [ ] MPI.2	Collective Communication (Broadcast, Scatter, Gather)

## Setup: 

* pull the class repo
* copy `week-3-mpi-collective` into your own repo
* add/commit/push the contents

## Description 

Following a lecture on collective communication protocols and the vector normalization task, implement parallelized vector norm.

Let's first operate under the assumption that the size of the array is evenly divisible by the number of tasks (pick an even number).  

Recall that vector normalization is $\frac{\hat{u}}{||u||}$

Recall the algorithm is as follows:

1. Generate vector on root (make sure N%p == 0)
2. scatter vector  to all nodes
3. all nodes calculate local sum-of-squares
4. all nodes send local sum back to root, root receives
5. root accumulates local sums, takes square root
6. root broadcasts sqrt to nodes
7. all nodes normalize their local vector
8. all nodes gather back to root node

In a file called `MPI_Normalize_Vector.c`, implement the normalization function.  You may use your Week 2 vector programs as starter code.

* you should have separate arrays for the original and result vector
* you can re-use the same array for `local-sum` and `local-norm`

## Tests:

 you'll know it works if the magnitude of the normalized vector is 1.  The magnitude is calculated by taking the square root of the sum of squares of the vector.  

 ## Analysis:

* calculate speedup for a range of vector sizes and tasks.  Use MPI timing code.

 ## Submit:
 *  add/commit/push your code and a `Writeup.md`

 ## Challenge: non-even slices

 Learn about `MPI_Scatterv`, and implement a version of vector normalization that works even when $N%P != 0$

---

## Part 2: Even/Odd Transposition Sort

Create a new file called `MPI_Sort.c` and implement the even/odd transposition algorithm discussed in lecture and in slides.  The algorithm is as follows:

1. On the root node generate a very large array of values
    * the size of the integer array should be passed in as an argument to the program via `argv`
    * for testing purposes the random seed can also be passed in as an argument (seed `srand` with `time(NULL)` if no second argument is given).
2. The root node should `scatter` slices of the array to all non-root nodes (Using scatter makes sure that root also gets a slice)
3. All nodes should then sort their local slices.  You don't have to be fancy here.  I've provided example code that uses the standard `qsort()` algorithm. 
4. Then the swapping/merging phases begin.  
    * In each case, pairs of adjacent nodes send each other their entire sorted array.  So each node will need to allocate space for an `otherslice` array.  I recommend learning about `MPI_Sendrecv` for this, to make your life easier.  
    * Once a node has both its slice and its neighbors slice, it needs to look through both arrays and keep exactly half of the items
        * the lower-id node keeps the smaller items between the two merged lists
        * the higher-id node keeps the larger items
        * at the end of this process the "kept" values need to be back in the node's local slice.
    * during the *even* phase, every even node pairs with the adjacent-higher odd node. (i.e. 0-1, 2-3, 4-5, etc)
    * during the *odd* phase, every odd node pairs with the adjacent-higher even node (i.e. 1-2, 3-4, 5-6, etc)
        * unpaired nodes do nothing.
5. Everything should be sorted after `p` phases (where p is the number of tasks).  This makes sense: if there is 1 task, then the list is sorted after 0 swap-merges.  If there are two tasks, you'll need 1 swap merge.   With 3 tasks you may need 3. Etc. 
6. When done, root node should `gather` the slices back to a big array.


### Writeup

Your writeup should provide nicely formatted markdown tables, with rows corresponding to various array sizes, and columns corresponding to number of processses.  Your writeup should also describe how your algorithm works, and provide some written analysis of why there is or is not speedup.
 
 
