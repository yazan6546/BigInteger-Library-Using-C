#include "LinkedList.h"
#include <stdlib.h>


/*
 * This function creates a linked list by first checking if there
 * is some other node that the pointer points to and freeing it if
 * such, and then allocates a memory block for the list, and finally
 * returns a pointer to the head of the list.
 */

struct node* makeEmpty(struct node* L) { //makeEmpty


    //checks if L points to some other node and deletes it if that is the case

    if (L != NULL) {
        deleteList(L);
    }
    L = malloc(sizeof(struct node)); //allocates memory for the new list

    if (L == NULL) {//checks if L is allocated successfully
        printf("out of memory!\n");
        exit(1);
    }

    L->data = 1;
    L -> next = L;
    L->previous = L;
    L->isHead = 1;
    return L;
}

/*
 * Linked list function that deletes all the list by
 * freeing each of its nodes as well as the head.
 */

void deleteList(struct node* L) {
    struct node *p = L->next;

    while (p!=L) { //deletes each of the nodes
        struct node *temp = p->next;
        free(p);
        p = temp;
    }
    free(L); //freeing the head
}


/*
 * Function that takes a head as input and returns
 * whether it is empty or not. The list is empty
 * if and only if the head node points to NULL.
 */
int isEmpty(struct node* L) {
    return L->previous == L; //
}

/*
 * Function that returns the size of the list not counting the head node.
 */

int getSize(struct node* L) {

    int size = 0;

    if (isEmpty(L)) { //checks if the list is empty
        return 0;
    }

    for (struct node* p = L->next; p!=L; p = p->next) {
        size++;
    }

    return size;
}

/*
 * Function that takes a head and data as input, and adds a node with said data
 * to the end of the list.
 */

void addLast(struct node* L, int data) {

    struct node* newNode = malloc(sizeof(struct node));

    if (newNode == NULL) { //checks if newNode has been successfully allocated.
        printf("Out of memory!");
        exit(1);
    }

    newNode->previous = L->previous;
    newNode -> next = L;
    L->previous->next = newNode;
    L->previous = newNode;
    newNode->data = data;
    newNode->isHead = 0;

    if (isEmpty(L)) {
        L->next = newNode;
    }
}

/*
 * Function that takes a head and data as input, and adds a node with said data
 * to the beginning of the list.
 */

void addFirst (struct node* L, int data) {

    struct node * newNode = malloc(sizeof(struct node));

    if (newNode == NULL) { //checks if newNode has been successfully allocated.

        printf("Out of memory!");
        exit(1);
    }


    if (!isEmpty(L)) {

        L->next->previous = newNode;
        newNode->next = L->next;

    }
    else {
        newNode->next = L;
        L->previous = newNode;
    }

    newNode->previous = L;
    L->next = newNode;
    newNode -> data = data;
    newNode->isHead = 0;
}


/*
 * Function that traverses and prints the contents of the list
 */

void printList(struct node* L, FILE *q) {

    if (isEmpty(L)) {
        fprintf(stdout, "The list is empty!\n");
        return;
    }

    for (struct node* p = L->next; p!=L;p = p->next) {
        fprintf(q, "%d", p->data);
    }
    fprintf(q, "\n");
}

/*
 * Function that takes a list as input and removes its first node
 * by freeing it.
 */

int removeFirst(struct node* L) {

    if (isEmpty(L)) {
        return 0; //returns 0 if the list is empty
    }

    int data = L->next->data;
    struct node* temp = L->next;
    temp->next->previous = L;
    L -> next = temp->next;
    free(temp);

    return data;
}

/*
 * Function that takes a list as input and removes its last node
 * by freeing it.
 */

int removeLast(struct node* L) {

    if (isEmpty(L)) {
        return 0; //returns 0 if the list is empty
    }

    int data = L->previous->data;

    struct node *p = L->previous->previous;
    free(L->previous);
    L->previous = p;
    p->next = L;

    return data;

}


/*
 * A function that copies the second list into the first, without altering the second. Returns
 * the copied list
 */

struct node* copyList (struct node *l2) {

    struct node *l1 = NULL;
    l1 = makeEmpty(l1); //creates an empty list

    l1->data = l2->data;

    for (struct node *p = l2->next;p!=l2;p = p->next) {
        addLast(l1, p->data);
    }

    return l1;
}

/*
 * Function that gets a list and empties its contents
 * excluding the head.
 */

void emptyList (struct node *L) {

    while (!isEmpty(L)) {
        removeLast(L);
    }
}


/*
 * Linked list prototype that returns a list representing a zero.
 */
struct node * createZero() {

    struct node *L = NULL;
    L = makeEmpty(L);
    L->data = 1;
    addFirst(L,0);

    return L;
}