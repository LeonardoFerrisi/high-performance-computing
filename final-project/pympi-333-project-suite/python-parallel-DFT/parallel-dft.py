from typing import final
from serialdft import Waves, SineWave, DFTSerial
import matplotlib.pyplot as plt
import numpy as np
from mpi4py import MPI
import time

class DFTParallel:
    
    def __init__(self, data, samplingRate, rank, comm, comm_sz):
        """
        Conducts a 'faster' DFT using MPI on uniform/repeating sequence
        sinewaves

        """
        # do regular thing

        # calculate the dft parallel
        if type(data)==SineWave:
            x = data.getData()
        else:
            x = data

        # print(len(data))
        # print(type(x))
        assert len(x) % comm_sz == 0 # Sinewave must be divisible by comm_sz

        self.lens = [] # would be a global thing


        self.sr = samplingRate
        self.N = len(x)

        self.lens.append(self.N)
        self.n = np.arange(self.N)
        self.k = self.n.reshape((self.N, 1))
        self.T = self.N/self.sr
        self.freq = self.n/self.T
        self.nyc = self.N//2
        self.fOneSide = self.freq[:self.nyc] 

        self.e = np.exp(-2j * np.pi * self.k * self.n / self.N)
        self.globalDFT = np.array(x)
        assert len(x) % comm_sz == 0
        self.finalDFT = None
        size = len(x)/comm_sz
        self.subDFT = np.zeros(int(size))    
        sendbuf = None
        finalSendBuf = None
        if rank == 0:
            sendbuf = self.globalDFT
        recvBuf = np.zeros(int(size))       

        comm.Scatter(sendbuf, recvBuf, root=0)

        d = DFTSerial(recvBuf, self.sr)
        finalSendBuf = d.DFT_Normal_oneside 

        for i in range(len(finalSendBuf)):

            finalSendBuf[i] = finalSendBuf[i]/comm_sz
            comm.allreduce(finalSendBuf[i], MPI.SUM)
                
        if rank == 0:
            self.finalDFT = np.array(finalSendBuf)
            self.DFT = self.finalDFT[:self.nyc]
        
    def plot(self, rank, figsize=(8, 6)):
        if rank==0:
            plt.figure(figsize = figsize)
            plt.stem(self.fOneSide[:(int(self.nyc/comm_sz))], abs(self.DFT), 'b', \
                        markerfmt=" ", basefmt="-b")

            # plt.plot(self.f_oneside, abs(self.DFT_Normal_oneside))
            plt.xlabel('Freq (Hz)')
            plt.ylabel('DFT Amplitude |X(freq)|')
            plt.show()


if __name__ == "__main__":
    comm = MPI.COMM_WORLD
    comm_sz = comm.Get_size()
    rank = comm.Get_rank()

    samplingRate = 64
    w = Waves(samplingRate, 32)
    w.addWave(freq=10, amplitude=1)
    w.addWave(freq=5, amplitude=2) 
    w.addWave(freq=12, amplitude=4) 
    w.addWave(freq=26, amplitude=5) 
    x = w.combineWaves()

    if rank==0:
        t1 = time.time()

    d = DFTParallel(x, samplingRate, rank, comm, comm_sz)

    if rank==0:
        t2 = time.time()
        d.plot(comm.Get_rank())


        timeElapsed = float(t2-t1)
        print(f"Time Elapsed: {round(timeElapsed*1000, 2)} ms")
