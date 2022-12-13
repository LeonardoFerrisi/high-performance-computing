"""
This file uses some borrowed code just to get some timing metrics.
I would have use numpy's builtin but wanted to have the code actuall written out
"""
from serialdft import SineWave, Waves
import numpy as np
import time

def DFT_slow(x):
    """
    Compute the discrete Fourier Transform of the 1D array x
    Borrowed from https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/
    """
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)

def FFT(x):
    """
    A recursive implementation of the 1D Cooley-Tukey FFT
    Borrowed from https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/
    """
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    # print(N)
    if N % 2 > 0:
        raise ValueError("size of x must be a power of 2")
    
    if N < 33:  # this cutoff should be optimized
        # print("DFT")
        return DFT_slow(x)
    if N > 35:
        # print(f"SHOULD NOT BE IN HERE: {N}")
        X_even = FFT(x[::2])
        X_odd = FFT(x[1::2])
        factor = np.exp(-2j * np.pi * np.arange(N) / N)
        try:
            return np.concatenate([X_even + factor[:N / 2] * X_odd,
                               X_even + factor[N / 2:] * X_odd])
        except:
            return None

if __name__ == "__main__":
    w = Waves(64, 32)
    w.addWave(freq=10, amplitude=1)
    w.addWave(freq=5, amplitude=2) 
    w.addWave(freq=12, amplitude=4) 
    w.addWave(freq=26, amplitude=5) 
    x = w.combineWaves()
   
    t1 = time.time()
    # breakpoint()
    f = FFT(x)
    t2 = time.time()
    timeElapsed = float(t2-t1)
    print(f"Time Elapsed: {round(timeElapsed*1000, 2)} ms")