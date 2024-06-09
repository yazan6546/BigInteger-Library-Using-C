#include "arithmetic.h"


/*
 * Function that takes 2 lists of numbers as input and returns
 * an array containing their division and remainder.
 */

struct node **divideAndRemainder (struct node *l1, struct node *l2) {

    int tempSign1 = l1->data;
    int tempSign2 = l2->data;

    struct node **array = malloc(2 * sizeof(struct node*)); //creates an array of 2 nodes

    struct node *division = NULL;
    division = makeEmpty(division);
    division->data = 1;

    struct node *remainder;

    l1->data = l2->data = 1;

    if (l2->next->data == 0) { //exits program if the divisor is zero

        printf("Error : dividing by zero!\n");
        exit(1);
    }

    int comp = compare(l1, l2); //compares the 2 numbers

    if (comp < 0) { //returns a division list representing 0 if the dividend is less than divisor
        //and a remainder same as the dividend.

        addFirst(division, 0);
        remainder = l1;
        array[0] = division;
        array[1] = remainder;

        return array;
    }
    else if (comp == 0) { //returns a list representing 0 if the dividend is less than divisor
        //and a remainder of zero.

        addFirst(division, 1);
        remainder = NULL;
        remainder = makeEmpty(remainder);
        addFirst(remainder, 0);

        array[0] = division;
        array[1] = remainder;

        return array;

    }

    int size = getSize(l2); //gets the size of l2
    int temp;

    struct node *mult;

    struct node *subList = NULL;
    subList = makeEmpty(subList);
    subList->data = 1;

    struct node *p = l1->next;

    /*
     * this loop creates a subList containing the first n numbers of the dividend l1, where n is the size of
     * the divisor l2.
     */
    for (int i = 0; i<size;i++) {
        addLast(subList, p->data);
        p = p->next;
    }

    /*
     * for loop that iterates over each of the digits of the dividend
     * then fetches the remainder of each micro division
     */
    for (;p != l1;p = p->next) {

        temp = divisionSubtract(subList, l2); //gets the division of the sublist over the divisor
        addLast(division, temp); //adds the value to the result
        mult = multiplyListByNumber(l2, temp);
        remainder = subtractNumbers(subList, mult); //gets the remainder of the micro-division
        addLast(remainder, p->data);    //continues division by adding to the remainder
        deleteList(mult); //frees lists
        deleteList(subList);
        subList = remainder;
        filterList(subList);
    }

    temp = divisionSubtract(subList, l2);
    addLast(division, temp);
    mult = multiplyListByNumber(l2, temp);
    remainder = subtractNumbers(subList, mult);


    division->data = tempSign1 * tempSign2;

    if (division->next->data == 0) { //removes the first redundant digit
        removeFirst(division);
    }

    l1->data = tempSign1;
    l2->data = tempSign2;

    array[0] = division;
    array[1] = remainder;

    deleteList(mult);

    return array;
}



/*
 * Internal Function that returns the division of 2 lists of numbers by
 * repeated subtraction. I.E how many times is the first subtracted by
 * the second before becoming less than l2.
 */

int divisionSubtract (struct node *l1, struct node *l2) {

    int count = 0;

    struct node *sub = subtractNumbers(l1, l2);
    struct node *temp = sub;

    while (sub->data != -1) { //loop stops when sub becomes negative.

        sub = subtractNumbers(sub, l2);
        deleteList(temp);
        temp = sub;
        count++;
    }
    return count;

}