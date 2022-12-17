import math
import sys

def calcpi(N):
    dx = 1/N
    sum = 0
    for i in range(1,N+1):
        w = dx
        xval = i*dx
        h = math.sqrt(1-(xval**2)) 
        sum += w*h
    pi = 4*sum
    print("estimate: ", pi, "actual: ",math.pi, "error: ", math.pi-pi)


if __name__ == "__main__":
    # myN = int(sys.argv[1])
    myN = 300000
    calcpi(myN)
