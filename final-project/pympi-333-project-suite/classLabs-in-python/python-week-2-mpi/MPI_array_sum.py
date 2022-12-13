import numpy as np
from mpi4py import MPI
import time

if __name__ == "__main__":

    comm = MPI.COMM_WORLD
    comm_sz = comm.Get_size()
    my_rank = comm.Get_rank()

    ArraySize = 233
    SomeBigArray = (3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6, 2, 8, 6, 2, 0, 8, 9, 9, 8, 6, 2, 8, 0, 3, 4, 8, 2, 5, 3, 4, 2, 1, 1, 7, 0, 6, 7, 9, 8, 2, 1, 4, 8, 0, 8, 6, 5, 1, 3, 2, 8, 2, 3, 0, 6, 6, 4, 7, 0, 9, 3, 8, 4, 4, 6, 0, 9, 5, 5, 0, 5, 8, 2, 2, 3, 1, 7, 2, 5, 3, 5, 9, 4, 0, 8, 1, 2, 8, 4, 8, 1, 1, 1, 7, 4, 5, 0, 2, 8, 4, 1, 0, 2, 7, 0, 1, 9, 3, 8, 5, 2, 1, 1, 0, 5, 5, 5, 9, 6, 4, 4, 6, 2, 2, 9, 4, 8, 9, 5, 4, 9, 3, 0, 3, 8, 1, 9, 6, 4, 4, 2, 8, 8, 1, 0, 9, 7, 5, 6, 6, 5, 9, 3, 3, 4, 4, 6, 1, 2, 8, 4, 7, 5, 6, 4, 8, 2, 3, 3, 7)

    i = None
    localSum = 0
    globalSum = 0

    blockSize = int(ArraySize / comm_sz)
    blockRemainder = int(ArraySize % comm_sz)
    my_first_i = int(my_rank * blockSize)
    my_last_i = int(my_first_i + blockSize)

    if (my_rank == comm_sz -1):
        my_last_i += blockRemainder
    
    i = my_first_i
    while i < my_last_i:
        localSum += SomeBigArray[int(i)]
        i+=1
    
    print(f"local sum of proces {my_rank} is {localSum}\n")

    t1 = time.time()

    if (my_rank != 0): # IF IS NOT RANK
        comm.send(localSum, dest=0, tag=11)

    else: # IF IS RANK
        q = None
        otherSum = None

        globalSum = localSum

        q = 1
        while q<comm_sz:
            otherSum = comm.recv(source=q, tag=11)
            globalSum += otherSum 
            q+=1
    
    t2 = time.time()
    timeElapsed = t2 - t1
    print(f"The global sum is: {globalSum}, time elapsed: [{timeElapsed*1000} ms]\n")




        