import numpy as np
import matplotlib.pyplot as plt
import time

class Waves:

    def __init__(self, samplingRate, seconds):
        """
        A class for storing many sin waves
        """
        self.sr = samplingRate
        self.time = seconds
        self.waves = []

    def addWave(self, freq, amplitude):
        s = SineWave(samplingRate=self.sr, freq=freq, amplitude=amplitude, seconds=self.time)
        self.t = s.getT()
        self.waves.append(s.getData())

    def combineWaves(self):
        self.combo = None
        for i in range(len(self.waves)):
            wave = self.waves[i]
            if i==0: 
                self.combo = wave
            else:
                self.combo += wave
            # print(np.shape(self.combo))
        return self.combo
    
    def plot(self, figsize=(8,6)):
        plt.figure(figsize = figsize)
        plt.plot(self.t, self.combo, 'r')
        plt.ylabel('Amplitude')
        plt.show()


class SineWave:
    """
    Generates a sine wave with specified samplingRate, frequnecy, 
    and amplitude over a specified amount of seconds
    """
    
    def __init__(self, samplingRate, freq, amplitude, seconds):
        
        # sampling rate
        sr = samplingRate
        
        # sampling interval
        ts = 1.0/sr # amount of cycles per second
        t = np.arange(0,seconds,ts)
        # print(t)
        
        self.time = t # multiply 

        freq = freq
        x = amplitude*(np.sin(2*np.pi*freq*t)) # generate sin waves

        self.waveform = x

        # print(np.shape(x))
        # freq = 20
        # x += np.sin(2*np.pi*freq*t) # Add sin wave to it

        # freq = 30
        # x += 4* np.sin(2*np.pi*freq*t)

    def getData(self):
        return self.waveform

    def getT(self):
        return self.time

    def plot(self, figsize=(8,6)):
        plt.figure(figsize = figsize)
        plt.plot(self.time, self.waveform, 'r')
        plt.ylabel('Amplitude')
        plt.show()



class DFTSerial:
    """
    Conducts a Discrete Fourier Transform on
    an input sinewave
    """
    
    def __init__(self, data, samplingRate):
        
        if type(data)==SineWave:
            x = data.getData()
        else:
            x = data

        self.sr = samplingRate                 # Get sampling Rate
        self.N = len(x)                        # Get length of signal
        self.n = np.arange(self.N)             # Create an array of N items numbered 0 - N
        self.k = self.n.reshape((self.N, 1))   # Reshape into an (N, 1) shaped array

        self.e = np.exp(-2j * np.pi * self.k * self.n / self.N) # Calculate the exponential of (-2i * pi * ((0,1,...,N), 1) * ( (0, 1, ..., N) / N ) )
        
        self.DFT = np.dot(self.e, x) # Get the dot product of e^(-2i * pi * ((0,1,...,N), 1) * ( (0, 1, ..., N) / N ) and signal x

        N = len(self.DFT) # Get the length of our new signal
        n = np.arange(N)  # Create an array of N items numbered 0 - N
        T = N/self.sr     # Divide the signal by sampling rate to get time scale
        self.freq = n/T   # Get the frequency by dividing everything in array by Time
        nyc = N//2        # The Nyquist Freq is equal to half of the signal length
        self.f_oneside = self.freq[:nyc] # Get only oneside of the frequency domain, since it is mirrored

        self.DFT_Normal_oneside =self.DFT[:nyc]/nyc # Normalize...

    def plot(self, figsize=(8, 6)):
        plt.figure(figsize = figsize)
        plt.stem(self.f_oneside, abs(self.DFT_Normal_oneside), 'b', \
                 markerfmt=" ", basefmt="-b")

        # plt.plot(self.f_oneside, abs(self.DFT_Normal_oneside))
        plt.xlabel('Freq (Hz)')
        plt.ylabel('DFT Amplitude |X(freq)|')
        plt.show()

if __name__ == "__main__":
    
    # s = SineWave(samplingRate=100, freq=5, amplitude=1, seconds=100)
    # s.plot()

    # d = DFTSerial(s, 100)
    # d.plot()


    w = Waves(64, 32) # 64 Hz, for 32 seconds
    w.addWave(freq=10, amplitude=1)
    w.addWave(freq=5, amplitude=2) 
    w.addWave(freq=12, amplitude=4) 
    w.addWave(freq=26, amplitude=5) 
    x = w.combineWaves()
    w.plot()    


    t1 = time.time()
    d = DFTSerial(x, 100)
    t2 = time.time()
    timeElapsed = float(t2-t1)
    print(f"Time Elapsed: {round(timeElapsed*1000, 2)} ms")
    d.plot()