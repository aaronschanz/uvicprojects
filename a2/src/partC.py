#!/bin/env python3
import sys
import re

def withSORT():
    Count_dict = {new_list: [] for new_list in range(35)}

    try:
        for i in range(len(sys.argv)-1):
            if (sys.argv[i+1] == "--infile"):
                data = open(sys.argv[i+2], "r")
    except Exception as e:
        print("The following error has occured:", e)
        return
    try:
        words = data.read()
    except Exception as e:
        print("Error:", e)
    splitWords = re.split("[ ;().,\n]", words)


    for i in range(35):
        Count_dict[i].append(0)
    
    for words in splitWords:
        if (len(words) is not 0):
            Count_dict[len(words)][0] += 1
            if (words not in Count_dict[len(words)]):
                Count_dict[len(words)].append(words)
 
    newDict1 = {k: v for k,v in sorted(Count_dict.items(), key = lambda x: x[1][0], reverse = True)}  
    
    for k,v in newDict1.items():
        if (v[0] is not 0):
            v[0] = str(v[0])
  
   
     
    def printing(key,value):        
        output = ""
        output += "(words: "  
        arr = newDict1[key][1:]
        arr = sorted(arr)
        for i in range(len(arr)):
            if len(arr) == 1:
                output += "\"" + arr[i] + "\""
            else:
                if (i == len(arr)-1):    
                    output += " and " + "\"" + arr[i] + "\""
                elif (i == len(arr)-2):
                    output += "\"" + arr[i] + "\""
                else:
                    output += "\"" + arr[i] + "\"" + ", "
        output += ")"
        return output    

 
    for k,v in newDict1.items():
        if (v[0] is not 0):
            print("Count[" + str(k).zfill(2) + "]=" + str(newDict1[k][0]).zfill(2) + ";" , printing(k,v)) 


def noSORT():
    Count_dict = {new_list : [] for new_list in range(35)}
    
    try:
        for i in range(len(sys.argv)-1):
            if (sys.argv[i+1] == "--infile"):
                data = open(sys.argv[i+2], "r")
    except Exception as e:
        print("The following error has occured:", e)
        return

    words = data.read()
    splitWords = re.split("[ ;().,\n]", words)

    for i in range(35):
        Count_dict[i].append(0)

    for words in splitWords:
        if (len(words) is not 0):
            Count_dict[len(words)][0] += 1                                       
            if (words not in Count_dict[len(words)]):
                Count_dict[len(words)].append(words)

    for i in range(35):
        if (Count_dict[i][0] is not 0 and i is not 0): 
            Count_dict[i][0] = str(Count_dict[i][0])
    
     
    def printing(index):        
        output = ""
        output += "(words: "  
        arr = Count_dict[index][1:]
        arr = sorted(arr)
        for i in range(len(arr)):
            if len(arr) == 1:
                output += "\"" + arr[i] + "\""
            else:
                if (i == len(arr)-1):    
                    output += " and " + "\"" + arr[i] + "\""
                elif (i == len(arr)-2):
                    output += "\"" + arr[i] + "\""
                else:
                    output += "\"" + arr[i] + "\"" + ", "
        output += ")"
        return output    

 
    for i in range(35):
        if (Count_dict[i][0] is not 0 and i is not 0):
            print("Count[" + str(i).zfill(2) + "]=" + str(Count_dict[i][0]).zfill(2) + ";" , 
            "(words:", printing(i))

def mainC():
    for i in range(len(sys.argv)-1):
        if (sys.argv[i+1] == "--sort"):
            withSORT()
            return
    noSORT()
    return
