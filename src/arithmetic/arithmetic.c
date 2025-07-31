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

    int len1 = getSize(p1);
    int len2 = getSize(p2);

    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    p1 = p1->next;
    p2 = p2->next;
    while (!p1->isHead && !p2->isHead) {
        if (p1->data > p2->data) {
            return 1;
        }
        if (p1->data < p2->data) {
            return -1;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    if (p1->isHead && p2->isHead) {
        return 0;
    }

    if (p2->isHead) {
        return 1;
    }

    return -1;
}
