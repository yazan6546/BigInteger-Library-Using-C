#include "arithmetic.h"


/*
 * Function to add 2 big numbers represented by a linked list, takes 2 lists as parameters and returns
 * a new list, each of the supplied lists is unaffected.
 */

/*
 * Function to add 2 big numbers represented by a linked list, takes 2 lists as parameters and returns
 * a new list, each of the supplied lists is unaffected.
 */

struct node* addNumbers (struct node *l1, struct node *l2) {

    struct node *sumList = NULL;
    sumList = makeEmpty(sumList);

    /*
     * redirects to subtraction if 2 signs are different
     * I.E (+5) + (-6) is the same as 5 - 6, so subtraction is appropriate here.
     */

    if ((l1->data * l2->data) < 0) {

        l2->data *= -1; //inverts the sign of the second list because as in 5 + -6, the 6 is considered to be
        //positive in the subtraction function, so it is inverted here to avoid unexpected results

        sumList = subtractNumbers(l1, l2); //redirects to subtraction
        l2->data *= -1;
        return sumList;
    }

    struct node *digit1 = l1->previous; //This linked list is circular so this is the last digit in list1
    struct node *digit2 = l2->previous; //This linked list is circular so this is the last digit in list2

    int carry, sum;
    carry = 0;

    /*
     * This for loop sums each of the discrete digits in each of the 2 lists by the traditional
     * addition algorithm, as in, there is a sum and carry after summing each of the corresponding
     * digits. It exits when one of the lists come to an end. Starts from the LSB to MSB.
     */

    for (; digit1 != l1 && digit2 != l2; digit1 = digit1->previous, digit2 = digit2->previous) {

        sum = (digit1->data + digit2->data) % 10; //I.E 1+9 = 0
        addFirst(sumList, sum + carry); //adds the sum to the list of result

        carry = (digit1->data + digit2->data) / 10; //I.E the carry of 9 + 1 is 1.
    }

    /*
     *if the size of the first list is bigger than that of the second or vice versa
     *then there will be some leftover digits in list1/list2, these are handled by
     *this function (moveDigitsSum()).
     */

    if (getSize(l1) > getSize(l2)) {
        moveDigitsSum(l1, sumList, digit1, carry);
    }

    else if (getSize(l1) < getSize(l2)) {

        moveDigitsSum(l2, sumList, digit2, carry);
    }

        /*
         * the previous function does not handle the case when the lists are equal in size
         * but there is a final carry I.E 9+8, so this line handles such.
         */

    else if (carry != 0) {
        addFirst(sumList, carry);
    }

    sumList->data = l2->data; //the sign of the result will be the same as the sign of one of them.
    //I.E -5 + -6 = -11, the sign of the result is negative. and if both were
    //positive then the sign will be positive.

    return sumList;
}



/*
 * Internal Function that handles the case when the lists are not equal in size
 * returns nothing, but modifies sumList.
 */
void moveDigitsSum (struct node* L, struct node* sumList, struct node* digit, int carry) {

    int sum;
    while (digit != L) {

        sum = digit->data + carry;
        addFirst(sumList, sum % 10);
        carry = sum / 10;
        digit = digit->previous;
    }

    if (carry != 0) {
        addFirst(sumList, carry);
    }
}