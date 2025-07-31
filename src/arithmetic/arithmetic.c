#include "arithmetic.h"

/*
 * Internal Function that removes any excessive zeros (zeros in the left), by
 * freeing each of these nodes.
 */

void filterList (struct node *l1) {

    struct node* digit = l1->next;

    while (digit->data == 0 && digit->next != l1) { //removes node if at the first of the list and is zero
        removeFirst(l1);
        digit = l1->next;
    }
}


/*
 * Internal Function to compare 2 lists of numbers. Takes 2 lists as input and
 * returns an int. 1 is l1 > l2, 0 if l1 == l2, -1 if l1 < l2.
 */

int compare (struct node *l1, struct node *l2) {

    struct node *p1 = l1;
    struct node *p2 = l2;

//    if (l1->data != l2->data) {
//        return l1 > l2 ? 1 : -1;
//    }
//    else if (p1->data == -1) { //both are negative, swap them
//
//        struct node *temp = p1;
//        p1 = p2;
//        p2 = temp;
//
//    }

    int len1 = getSize(p1);
    int len2 = getSize(p2);

    if (len1 > len2)
        return 1;
    if (len2 > len1)
        return -1;

    p1 = p1->previous;
    p2 = p2->previous;
    while (!p1->isHead && !p2->isHead) {
        if (p1->data > p2->data) {
            return 1;
        }
        else if (p1->data < p2->data) {
            return -1;
        }

        p1 = p1->previous;
        p2 = p2->previous;
    }

    if (p1->isHead && p2->isHead) {
        return 0;
    }

    if (p2->isHead) {
        return 1;
    }

    return -1;
}
