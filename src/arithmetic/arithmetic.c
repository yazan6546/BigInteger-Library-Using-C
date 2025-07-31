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

    if (isEmpty(l1) || isEmpty(l2)) {
        return 0; // Invalid BigInt
    }

    if (l1->next->data == 0 && l2->next->data != 0) {
        return -1 * l2->data; // l1 is zero, so l2 is greater or equal
    }
    if (l2->next->data != 0 && l1->next->data == 0) {
        return l1->data; // l2 is zero, so l1 is greater or equal
    }

    if (l1->data != l2->data) {
        return l1->data > l2->data ? 1 : -1; // Compare signs
    }

    // Both numbers have the same sign, so we compare their sizes

    int len1 = getSize(p1);
    int len2 = getSize(p2);

    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    // Compare digits starting from the first digit after the head
    // Signs are equal (positive positive or negative negative)

    p1 = p1->next;
    p2 = p2->next;
    while (!p1->isHead && !p2->isHead) {


        if (p1->data > p2->data) {
            return 1 * l1->data; // Reverse the result to accomodate sign
        }
        else if (p1->data < p2->data) {
            return -1 * l1->data; // Reverse the result to accomodate sign
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    return 0;
}
