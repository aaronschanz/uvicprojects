//Header file to work with word_count.c and list.c

#ifndef  _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct node {
    int length;
    char *word;
    struct node *next;
} node;

node *new_node(int length, char *word);
node *add_inorder(node *list, node *new);

#endif
