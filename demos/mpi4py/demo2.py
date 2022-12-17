from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    data = [3,1,4,1]
else:
    data = None
comm.bcast(data,root=0)
#comm.scatter(data, root=0)
if rank != 0:
    print(rank, data)