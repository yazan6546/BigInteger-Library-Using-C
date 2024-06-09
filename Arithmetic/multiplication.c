#include "arithmetic.h"

/*
 * Internal Function that takes a number and a list and returns their
 * product as a list.
 */

struct node* multiplyListByNumber (struct node *l1, int number) {

    struct node* list = NULL;
    list = makeEmpty(list);

    struct node *digit;
    int mult;
    int carry = 0;

    /*
     * This for loop multiplies each of the digits in the list by
     * the number supplied.
     */

    for (digit = l1->previous;digit != l1;digit = digit->previous) {

        mult = (digit->data * number) % 10;
        addFirst(list, mult + carry);
        carry = (digit->data * number) / 10;

    }

    if (carry != 0) { //adds the last carry to the list
        addFirst(list, carry);
    }
    list->data = 1;
    filterList(list); //removes any redundant zero.
    return list;
}



/*
 * Function that multiplies 2 lists of numbers and returns the result as another list.
 */

struct node* multiplyNumbers (struct node *l1, struct node *l2) {

    struct node *sum = NULL;
    sum = makeEmpty(sum);

    sum->data = 1;
    addFirst(sum, 0); //initializes the sum list to add to it

    if (l1->next->data == 0 || l2->next->data == 0) { //if one of the lists are equal to zero, then zero will be
        //returned.
        return sum;
    }

    struct node *digit = l2->previous; //make digit point to the last digit in the list
    struct node *temp = NULL;
    struct node *tempSum = NULL;

    for (int j = 0; digit != l2; digit = digit->previous, j++) {

        temp = multiplyListByNumber(l1, digit->data);

        for (int i = 0; i < j; i++) { //adds a zero depending on the number weight.
            addLast(temp, 0);
        }
        tempSum = sum;
        sum = addNumbers(temp, sum); //adds all lists together

        deleteList(tempSum);
        deleteList(temp);
    }

    sum->data = (l1->data) * (l2->data); //the sign of the result will be the same as
    //the product of their signs. I.E 2* -3 = -6
    return sum;
}
