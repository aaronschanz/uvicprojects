#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "list.h"

//Name: Aaron Schanz
//ID: V00936095


node *new_node(int length, char *word) {
    
    node *temp = (node*)malloc(sizeof(node));

    if (temp == NULL) {
        fprintf(stderr, "malloc failed");
        exit(3);
    }

    temp->length = length;
    temp->next = NULL;
    temp->word = strdup(word);

    return temp;
}


node *add_inorder_noSort(node *list, node *new) {
    node *prev = NULL;
    node *curr = NULL;

    if (list == NULL) {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        if (new->length > curr->length) {
            prev = curr;
            continue;
        } else if (new->length == curr->length) {
            if (strcmp(new->word, curr->word) < 0) {
                break;
            } else {
                prev = curr;
                continue;
            }
        } else {
            break;
        }
    }

    new->next = curr;
    
    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return list;
    } 
}

node *add_inorder_withSort(node *list, node *new) {
    node *prev = NULL;
    node *curr = NULL;

    if (list == NULL) {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        if (new->length > curr->length) {
            prev = curr;
            continue;
        } else if (new->length == curr->length) {
            if (strcmp(new->word, curr->word) > 0) {
                break;
            } else {
                prev = curr;
                continue;
            }
        } else {
            break;
        }
    }

    new->next = curr;
    
    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return list;
    } 
}



void print_list(node *p) {
    while (p != NULL) {
        printf("%d%s%s\n", p->length, "+", p->word);
        p = p->next;
    }
}

int longest_length(node *p) {
    int max = 0;
    while (p != NULL) {
        if (p->length > max) {
            max = p->length;
        }
        p = p->next;
    }
    return max;
}

int doesWordExist(node *p, char *word) {
    while (p != NULL) {
        if (strcmp(p->word, word) == 0) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int count(node *p, int x) {
    node *curr = p;
    if (curr == NULL)
        return 0;
    if (curr->length == x)
        return 1 + count(p->next, x);
    return count(p->next,x);
}

void printWordsNoSort(node *p, int x, int y) { 
    if (p == NULL) {
        return;
    }
 
    if (p->length == x && strcmp(p->word,"") != 0) { 
        //case where the next node is not null and the length changes 
        if (p->next != NULL && p->next->length != x) {
            //if p->word is the only of its length
            if (y == 1) {
                printf("%s%s%s", "\"", p->word, "\"");
            // if the next node is null and there is more than one word of this length, we add and 
            } else {
                printf("%s%s%s", "and \"", p->word, "\""); 
            }   
        }
        //case where its the last element of the list so its just the word no comma or and 
        else if (p->next == NULL) {
            printf("%s%s%s", "\"", p->word, "\"");
        }
        //case where the next next node length changes and we dont add a comma  
        else if(p->next->next != NULL && p->next->next->length != x) {
            printf("%s%s%s", "\"", p->word, "\" ");
        } 
        //case where its the second last element of the list 
        else if (p->next->next == NULL) {
            printf("%s%s%s", "\"", p->word, "\" and ");
        } 
        else {
            printf("%s%s%s" , "\"", p->word, "\", ");
        }
    } 
    printWordsNoSort(p->next, x, y);  
}
 

void printWordsWithSort(node *p, int x, int y) { 
     if (p == NULL) {
        return;
    }
 
    if (p->length == x && strcmp(p->word,"") != 0) { 
        //case where its the last element of the list no and or commas
        if (p->next == NULL) {
            printf("%s%s%s", "\"", p->word, "\""); 
        }
        else if (p->next != NULL && p->next->length != x) {
            printf("%s%s%s", "\"", p->word, "\"");
        }
        else if (p->next->next != NULL && p->next->next->length == x && strcmp(p->next->next->word, "") == 0) {
         if (p->next->next->next != NULL && p->next->next->next->length == x && strcmp(p->next->word, "") != 0) {
                printf("%s%s%s", "\"", p->word, "\" and ");
            } else {
                printf("%s%s%s", "\"", p->word, "\"");
            }
        }
        else if(p->next->next == NULL && p->next->length == x) {
            printf("%s%s%s", "\"", p->word, "\" and ");
        }
        //case where the next next node is not null and the length changes
        else if (p->next->next != NULL && p->next->next->length != x) {
            //if word only occurs once
            if (y == 1) {
                printf("%s%s%s", "\"", p->word, "\"");
            } 
            //if the next next node is not null and the word of the next node is "" 
            else if (strcmp(p->next->word, "") == 0){
                printf("%s%s%s", " and \"", p->word, "\"");
            } 
            //if the next word is not ""
            else {
                printf("%s%s%s", "\"", p->word, "\" and ");
            }
        }  
        else {
            printf("%s%s%s", "\"", p->word, "\", ");
        }
    }    
    printWordsWithSort(p->next, x, y);    
} 


int withSORT(int argc, char *argv[]) {
    FILE *data = NULL;
    char* words;
    char* token;
    node *list = NULL; 
   
    //opening the file 
    for (int i = 0; i<argc; i++) {
        if (strcmp(argv[i], "--infile") == 0) {
            data = fopen(argv[i+1], "r");
        }
    }
 
    if (data == NULL) {
        fprintf(stderr, "unable to open badfile.txt for reading");
        exit(2);     
    }
     
    //filelength is how many characters there are in the text file.
    fseek(data, 0L, SEEK_END);
    int filelength = (int) ftell(data);
    words = (char*)malloc(filelength*sizeof(char)+1);    

    if (words == NULL) {
        fprintf(stderr, "malloc failed");
        exit(3);
    }
    words[filelength] = 0;   
    //copies the text from data into words 
    fseek(data, 0,  SEEK_SET);
    fread(words, sizeof(char), filelength, data);
    
    
    //tokenizing through words and adding the nodes to list
    token = strtok(words, "\t\r\f\v\n ,.;()");
    
    while (token != NULL) {
        if (doesWordExist(list,token) == 0) {    
            list = add_inorder_withSort(list, new_node(strlen(token), token));
        } else if (doesWordExist(list,token) == 1) {
            list = add_inorder_withSort(list, new_node(strlen(token), ""));
        }
        token = strtok(NULL, "\t\r\f\v\n ,.;()");
    }
    
    //helper array to store the frequency of word lengths
    int *counts = (int*)malloc(longest_length(list)*sizeof(int*));
    if (counts ==  NULL) {
        fprintf(stderr, "malloc failed");
        exit(3);
    } 
    
    for (int i = 0; i <= longest_length(list); i++) {
        counts[i] = count(list,i);
        if (counts[i] != 0) { 
            printf("%s%02d%s%02d%s", "Count[", i, "]=", counts[i], ";");
            printf("%s", " (words: "); 
            printWordsWithSort(list,i, counts[i]);
            printf("%s\n", ")");
        }
    }
   
    free(counts); 
    free(words);
    fclose(data);

    node *temp = NULL;
    for ( ; list != NULL; list = temp) {
        temp = list->next;
        free(list->word);
        free(list);
    }
    
    
  
}



 int noSORT(int argc, char *argv[]) {
    FILE *data = NULL;
    char *words;   
    char *token;
    node *list = NULL;    
 
    //opening the file 
    for (int i = 0; i<argc; i++) {
        if (strcmp(argv[i], "--infile") == 0) {
            data = fopen(argv[i+1], "r");
        }
    }
    
    if (data == NULL) {
        fprintf(stderr, "unable to open badfile.txt for reading");
        exit(2);     
    }

    //filelength is how many characters there are in the text file.
    fseek(data, 0L, SEEK_END);
    int filelength = (int) ftell(data);
    words = (char*)malloc(filelength*sizeof(char)+1);
        
    if (words == NULL) {
        fprintf(stderr, "malloc failed");
        exit(3);
    }
 
    words[filelength] = 0;
    //copies the text from data into words 
    fseek(data, 0,  SEEK_SET);
    fread(words, sizeof(char), filelength, data);
    
    //tokenizing through words and adding the nodes to list
    token = strtok(words, "\t\r\f\v\n ,.;()");
    while (token != NULL) {
        //if the word doesn't exist in the list yet, add a new node with the word length and the word
        if (doesWordExist(list,token) == 0) {    
            list = add_inorder_noSort(list, new_node(strlen(token), token));
        //if the word already exists in the list, add a new node with only the length of the word    
        } else if (doesWordExist(list,token) == 1) {
            list = add_inorder_noSort(list, new_node(strlen(token), ""));
        }
        token = strtok(NULL, "\t\r\f\v\n ,.;()");
    }
    
    //helper array to store the frequency of word lengths      
    int *counts = (int*)malloc(longest_length(list)*sizeof(int*));
    if (counts == NULL) {
        fprintf(stderr, "malloc failed");
        exit(3);
    }
 
    for (int i = 0; i <= longest_length(list); i++) {
        counts[i] = count(list,i);
        if (counts[i] != 0) { 
            printf("%s%02d%s%02d%s", "Count[", i, "]=", counts[i], ";");
            printf("%s", " (words: "); 
            printWordsNoSort(list,i, counts[i]);
            printf("%s\n", ")");
        }
    }

    free(counts);
    free(words); 
    fclose(data);
 
    node *temp = NULL;
    for ( ; list != NULL; list = temp) {
        temp = list->next;
        free(list->word);
        free(list);
    }

} 
 
int main(int argc, char *argv[]) {
    for (int i = 1; i<argc; i++) {
        if (strcmp(argv[i], "--sort") == 0) {
            return withSORT(argc, argv);
        }
     }   

    for (int i = 0; i<argc; i++) {
        if (strcmp(argv[i], "--infile") == 0) {
            return noSORT(argc, argv);
        }
    }
    fprintf(stderr, "Invalid or no command line arguments");
    exit(1);
}

