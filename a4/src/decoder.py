#!/usr/bin/env python3

"""
Provided for you is the encryption alphabet used to encrypt the provided files.
This inclues: a-z, A-Z, 0-9, punctuation like .(); (not the same as in a1-a3), space and newline
"""
from cipher import FileDecoder, DecryptException
import string
import re
alphabet = string.ascii_lowercase + string.ascii_uppercase + string.digits + string.punctuation + " \n"

#this function regex checks the inputted password
def isPass(key):
    if re.match(r'^.{6,8}$', key):
        if re.search(r'[A-Z]+', key):
            if re.search(r'([0-9].*){2,}', key):
                if re.search(r'^([^!@#\$&\*\-_\.\"\'%\(\)\+,/:;<=>\?\[\]\\\^\{\}\|`~])*([!@#\$&\*\-_\.])([^!@#\$&\*\-_\.\"\'%\(\)\+,/:;<=>\?\[\]\\\^\{\}\|`~])*([!@#\$&\*\-_\.])([^!@#\$&\*\-_\.\"\'%\(\)\+,/:;<=>\?\[\]\\\^\{\}\|`~])*$', key): 
                    #IF ALL CHARACTERS ARE IN ALPHABET 
                    return True
    
    return False
    
#this function gets the name of the file when the file is found
def getFile():
    filename = input("Enter the name of file: ")
    
    if (filename == "q"):
        exit(0)

    try:
        data = open(filename, "r")
        data.close()
    except FileNotFoundError:
        print("Invalid file.")
        return getFile()
  
    return filename

#this function gets the key if it passes the regex  check
def getPass():
    password = input("Enter password: ")
        
    if (password == "q"):
        exit(0)
        
    if (isPass(password)):
        return password
    else:
        print("Invalid password. Failed regex check.")
        return getPass()

def average(text):
    myDict = {1:[0,0], 2:[0,0], 3:[0,0], 4:[0,0], 5:[0,0], 6:[0,0], 7:[0,0], 8:[0,0], 9:[0,0], 10:[0,0], 11:[0,0], 12:[0,0]}
 
    while True:
        try:
            sum = 0
            temp = next(text)
            line = temp.split(",")
            sum = ((int(line[11])-int(line[6]))*60+(int(line[12])-int(line[7])))
            myDict[int(str(line[4]).strip("0"))][1] += 1
            myDict[int(str(line[4]).strip("0"))][0] += sum
        except StopIteration:
            break
    return myDict
    
def getMonth(num):
    if num == 1:
        return "Jan"
    elif num == 2:
        return "Feb"
    elif num == 3:
        return "Mar"
    elif num == 4:
        return "Apr"
    elif num == 5:
        return "May"
    elif num == 6:
        return "Jun"
    elif num == 7:
        return "Jul"
    elif num == 8:
        return "Aug"
    elif num == 9:
        return "Sep"
    elif num == 10:
        return "Oct"
    elif num == 11:
        return "Nov"
    elif num == 12:
        return "Dec"
        
#global variable to set the filename
filename = getFile()
def main():
    try:
        file_decoder = FileDecoder(filename, getPass(), alphabet)
    #this except block catches any DecryptionException, which are raised if key is invalid
    except DecryptException as e:
        print("Invalid password (DecryptException). Please try again.")
        return main()
    print("\nRESULTS\n" + "FileDecoder:", file_decoder)
    print("Entries:" , len(file_decoder)) 
    dict = average(file_decoder)
    for k,v in dict.items():
        if v[1] is not 0:
            print("    Average delay for " + getMonth(k) + ": " + "{0:.2f}".format(v[0]/v[1]))
    print("END")

main()
