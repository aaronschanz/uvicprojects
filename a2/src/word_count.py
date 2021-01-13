#!/bin/env python3
import sys
import re
import partA
import partB
import partC

def main():
    
    if ("--infile" not in sys.argv):
        print("Error, did not include --infile")
        return
 
    if (len(sys.argv) < 3):
        print("program: missing \'--infile <filename> [--sort] [--print-words]\'")

    for i in range(len(sys.argv)-1):
        if (sys.argv[i+1] == "--print-words"):
            partC.mainC()
            return

    for i in range(len(sys.argv)-1):
        if (sys.argv[i+1] == "--sort"):
            partB.mainB()
            return    

    for i in range(len(sys.argv)-1):
        if (sys.argv[i+1] == "--infile"):
            partA.mainA()
            return
        else:
            print("No arguments found")
            return

#Do not change this
if __name__ == "__main__":
    main()


