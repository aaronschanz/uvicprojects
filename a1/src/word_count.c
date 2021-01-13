#include "word_count.h" 

//Name: Aaron Schanz
//ID: V00936095


int partA(int argc, char *argv[]) {
    
    char inputline[750];          // intializing data
    char *token;
    int Count[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    FILE *data = NULL;
    
    for (int i = 1; i<argc; i++) {        // checks which of the arguments are --infile, then opens the text file one over, as text file is always right of --infile
        if (strcmp(argv[i], "--infile") == 0) {
            data = fopen(argv[i+1], "r");
        }
    }   
 
    if (data == NULL) {             // in case no argument --infile was found, will return an error
        printf("%s\n", "unable to open 'badfile.txt' for reading");
        return -1;
    }

    while (fgets(inputline,MAX_FILESIZE,data) != NULL) {   // while loop will take one line at a time from the opened text file and convert it into strings in inputline
        token = strtok(inputline, "\t\r\f\v\n ,.;()");    // setting the first token to the first word of the inputline
        if (token != NULL) {                             
            long int arg = strlen(token);                // increasing Count by 1 at the place of the length of the token -1
            Count[arg-1]++;
        }
        while (token != NULL) {                         
            token = strtok(NULL, "\t\r\f\v\n ,.;()");   // setting the next token equal to the next word in inputline
            if (token != NULL) {
                long int arg = strlen(token);
                Count[arg-1]++;                         // again, increasing Count at the index of length of token -1
            }
        }
    }
   
    for (int i = 0; i < 35; i++) {
        if (Count[i] != 0) { 
            printf("%s%02d%s%02d%s\n","Count[",i+1, "]=", Count[i], ";");
        }                                                                           // this for loop prints the desired result.
    }

    fclose(data);

    return 0;
}


int partB(int argc, char *argv[]) {

    char inputline[750];
    char *token;
    int Count[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    FILE *data = NULL;
    
    for (int i = 1; i<argc; i++) {
        if (strcmp(argv[i], "--infile") == 0) {
            data = fopen(argv[i+1], "r");
        }
    }   
 
    if (data == NULL) {
        printf("%s\n", "unable to open 'badfile.txt' for reading");
        return -1;
    }

    while (fgets(inputline,MAX_FILESIZE,data) != NULL) {
        token = strtok(inputline, "\t\r\f\v\n ,.;()");
        if (token != NULL) {
            long int arg = strlen(token);
            Count[arg-1]++;
        }
        while (token != NULL) {
            token = strtok(NULL, "\t\r\f\v\n ,.;()");
            if (token != NULL) {
                long int arg = strlen(token);
                Count[arg-1]++;
            }
        }
    }

    int max;
    int maxIndex;   
    
    typedef struct str {
        int value;
        int index;
    } str;
    
    struct str CountStr[35];
    for (int i = 0; i < 35; i++) {                // created a struct array to make the sorting easier and copied Count to CountStr by index and value
        CountStr[i].value = Count[i];
        CountStr[i].index = i;
    }
    
    //sorting algorithm taken from www.sanfoundry.com
    for (int i = 0; i < 35; i++) {
        for (int j = i+1; j < 35; j++) {
            if (CountStr[i].value < CountStr[j].value) {
                max = CountStr[i].value;
                maxIndex = CountStr[i].index;
                CountStr[i].value = CountStr[j].value;
                CountStr[i].index = CountStr[j].index;
                CountStr[j].value = max;
                CountStr[j].index = maxIndex;
            }
        }
    }
    
    for (int i = 0; i < 35; i++) {                    // printing results
        if (CountStr[i].value != 0) {
            printf("%s%02d%s%02d%s\n", "Count[", CountStr[i].index+1, "]=", CountStr[i].value, ";");
        }
    }
  
    float nums[35];                      
    int count = 0;
    for (int i = 0; i < 35; i++) {         // creating an array to hold the set of string lengths
        if (Count[i] != 0) {               // if Count[i] != 0, there are words of length i+1 in the file
            nums[count] = i+1;             // in nums, linearly placing values of string lengths in the array
            count++;
        }
    }

    if (count == 0) {
        printf("%s%.1f\n", "Median word length: ", 0.0);          // if there is no words in the file
    } else if (count % 2 == 0) {                                   
        float avg = 0.0;
        avg = (nums[count/2]+nums[(count/2)-1])/2;               // if there is an even number in the set of string lengths, calculates the average
        printf("%s%.1f\n","Median word length: ", avg);
    } else {                                          
        printf("%s%.1f\n","Median word length: ", nums[(count-1)/2]);      // if there is an odd number in the set of string lengths, calculates the middle value.
    }
          
    return 0;
}


int partC(int argc, char *argv[]) {
    return 0;
}

int
real_main(int argc, char *argv[]) {
    
    if (argc < 3) {              // checks if less than 3 arguments were inputted, as this means either a text file or argument is missing
        printf("%s\n","program: missing '--infile <filename> [--sort] [--print-words]'");
        return -1;
    }

    for (int i = 1; i<argc; i++) {             // checks if an argument is print--words... if yes, it will run partC
        if (strcmp(argv[i], "--print-words") == 0) {
            return partC(argc,argv);
        }
    }
 
    for (int i = 1; i<argc; i++) {           // checks if an argument is --sort... if yes, it will run partB
        if (strcmp(argv[i], "--sort") == 0) {
            return partB(argc,argv);
        }
    }
    
    for (int i = 1; i<argc; i++) {           // checks if an argument is --infile... if yes, it will run partA
        if (strcmp(argv[i], "--infile") == 0) {
            return partA(argc,argv);
        } else {
             printf("%s\n","No Arguments found");
             return -1;
       }
    }

    return 0;
}


#ifndef TEST
int
main(int argc, char *argv[]) {   
    return real_main(argc, argv);
}
#endif
