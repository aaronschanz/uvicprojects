#!/bin/env python3
import sys
import re

def mainA():
    
    Count = [0] * 35
    
    try:
        for i in range (len(sys.argv)-1):
            if (sys.argv[i+1] == "--infile"):
                data = open(sys.argv[i+2],"r")
    except Exception as e:
        print("The following error has occured:",e)
        return

    words = data.read()
    splitWords = re.split("[ ;().,\n]", words)

    for words in splitWords:
        Count[len(words)] += 1
   
    for i in range(35):
        if (Count[i] is not 0 and i is not 0):
            print("Count[" + str(i).zfill(2) + "]=" + str(Count[i]).zfill(2) + ";")
