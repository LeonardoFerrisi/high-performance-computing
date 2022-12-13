# i = [0,1,2,3,4,5,6,7,8,9,10,11, 12]
# # get indices:
# print(len(i))
# comm_sz = 4
# ourLen = int(len(i) / comm_sz)

# add = 0
# if len(i) % comm_sz !=0:
#     add = len(i) % comm_sz

# for j in range(comm_sz):
#     start = ourLen*j
#     end = start+ourLen
#     if j==comm_sz-1:
#         end+=add
#     print(f"s:{start} e:{end}\n")

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    data = [3,1,4,1,5]
    comm.send(data, dest=1, tag=11)
elif rank == 1:
    data = comm.recv(source=0, tag=11)
    print(data)