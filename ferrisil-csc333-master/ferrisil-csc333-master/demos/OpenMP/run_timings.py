import os
import string
import sys
from subprocess import call
import subprocess

#Author: John Rieffel

def GetTimings(bin_name, args):
        '''
        iterate through a list of command line arguments
        and call bin_name with those arguments
        '''
        for arg in args:
                argv = [str(a) for a in arg]
                argstr = " ".join(argv)
                syscall = "./"+bin_name + " " + argstr
                #print(syscall)
                os.system(syscall)
      

if __name__ == '__main__':
        bin_name= sys.argv[1]
        #better maybe to create this list of arguments programatically?
        my_args = [(1,1,0),(2,1,0),(4,1,0)]
        GetTimings(bin_name,my_args)

