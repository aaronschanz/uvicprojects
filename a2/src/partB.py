#!/bin/env python3
import sys
import re

def mainB():
    
    Count = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35]
    Count_dict = {nr: 0 for nr in Count} 
    
    try:
        for i in range(len(sys.argv)-1):
            if (sys.argv[i+1] == "--infile"):
                data = open(sys.argv[i+2],"r")
    except Exception as e:
        print("The following error has occured:", e)
        return

    words = data.read()
    splitWords = re.split("[ ;().,\n]", words)
     
    for word in splitWords:
        if (len(word) is not 0):
            Count_dict[len(word)] += 1

    newDict = {k: v for k,v in sorted(Count_dict.items(), key = lambda item: item[1], reverse = True)}    
    
    count = 0
    keys = []
    for k, v in newDict.items():
        if (v is not 0):
            print("Count[" + str(k).zfill(2) + "]=" + str(v).zfill(2) + ";")
            count += 1
    
    for k, v in Count_dict.items():
        if (v is not 0):
            keys.append((k,v))

    if (count is 0):
        print("Median word length: 0.0")
    elif (count % 2 is 0):
        print("Median word length:",(keys[int(count/2)][0] + keys[int((count/2)-1)][0])/2)
    else: 
        print("Median word length:", "{:.1f}".format(keys[int((count-1)/2)][0]))
