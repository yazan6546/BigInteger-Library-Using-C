#ifndef PROJ_LINKEDLIST_H
#define PROJ_LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

struct node {

    int data;
    struct node* next;
    struct node* previous;
    char isHead;
};



struct node* makeEmpty(struct node* L);
void deleteList(struct node* L);
int isEmpty(struct node* L);
int getSize(struct node* L);
void addLast(struct node* L, int data);
void addFirst (struct node* L, int data);
void printList(struct node* L, FILE *q);
int removeFirst(struct node* L);
int removeLast(struct node* L);
struct node* copyList (struct node *l1, struct node *l2);
void emptyList (struct node *L);
#endif //PROJ_LINKEDLIST_H
