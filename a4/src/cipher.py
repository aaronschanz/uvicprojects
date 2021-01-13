#!/usr/bin/env python3
import re

"""
In this file, you need to add your FileDecoder class
See a4 PDF for details

WE WILL EVALUATE YOUR CLASS INDIVIDUAL, SO MAKE SURE YOU READ
THE SPECIFICATIONS CAREFULLY.
"""
class DecryptException(Exception):
    pass

class FileDecoder:
    def __init__(self, filename, key, alphabet):
        self.key = key
        self.filename = filename
        self.alphabet = alphabet
        self.i = 0
        
        #this section decodes the input file
        text = open(filename, "r")
        encoded = []
        pos = 0
        for line in text:  
            for char in line:
                new = (alphabet.find(char)-alphabet.find(key[pos%len(key)]))%len(alphabet)
                pos += 1
                encoded.append(alphabet[new])
        test = []
        for char in encoded:
            if (char != "\n"):
                test.append(char)
            else:
                break
        
        #checking to see if the file is decoded properly, if not an exception is raised and function restarts
        count = 0
        for char in test:
            if char == ",":
                count += 1
        if count != 17:
            raise DecryptException(DecryptException)         
        else:
            self.encoded = encoded
        

    #prints the FileDecoder
    def __str__(self):
        return "FileDecoder(key=\'"+ self.key +"\', file=\'"+ self.filename + "\')" 
    
    #returns the count of decoded rows 
    def __len__(self):
        count = 0
        for char in self.encoded:
            if char == "\n":
                count += 1
        return count
        
    #function to make the class iterable
    def __iter__(self):
        return self 
    
    #function to iterate over decoded rows
    def __next__(self):
        list = "".join(self.encoded)
        try: 
            self.i += 1
            return list.splitlines()[self.i]
        except IndexError:
            raise StopIteration 
        
       
    

         
   
