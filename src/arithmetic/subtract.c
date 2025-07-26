#include "arithmetic.h"

/*
 * Function that takes 2 lists of big integers and returns their difference as a list. Each of the lists
 * is unaffected in the process.
 */

struct node* subtractNumbers (struct node *l1 , struct node *l2) {

    struct node *subtractList = NULL;
    subtractList = makeEmpty(subtractList);

    /*
    * redirects to subtraction if the 2 signs are different
    * I.E (-5) + (-6) is the same as -(5 + 6), so addition is appropriate here.
    */

    if ((l1->data) * (l2->data) < 0) {

        l2->data *= -1;  //inverts the sign of the second list because as in (-)5 - (+)6, the 6 is considered to be
        //negative in the addition function, so it is inverted here to avoid unexpected results

        subtractList = addNumbers(l1, l2); //redirects to addition
        l2->data *= -1;
        return subtractList;
    }
    int n = compare(l1, l2); //compares the sizes of l1 and l2.

    if (n == 0) { //returns a list representing zero if both are equal
        return createZero();
    }

    else if (n < 0) { //swaps both lists if the first is less than the second and inverts the sign after. I.E 5-6 = -(6-5).
        struct node *temp = l1;
        l1 = l2;
        l2 = temp;
    }


    struct node *temp1 = NULL;  //creating a temp list just not to modify the value of l1
    temp1 = makeEmpty(temp1);
    copyList(temp1, l1); //copying l1 into temp1
    struct node *digit1 = temp1->previous;

    struct node *temp2 = NULL;  //creating a temp list just not to modify the value of l2
    temp2 = makeEmpty(temp2);
    copyList(temp2, l2); //copying l2 into temp2

    struct node *digit2 = temp2->previous; //make temp2 point to the last digit in list 2.

    /*
     *This for loop selects each digit in the list and subtracts each by each. Stops
     * when one of the lists reach to an end.
     */

    for (; digit1 != temp1 && digit2 != temp2; digit1 = digit1->previous, digit2 = digit2->previous) {


        if (digit1->data < digit2->data) { //calls the borrow function when a digit is less the corresponding one.
            borrow(temp1, digit1);
        }

        addFirst(subtractList, digit1->data - digit2->data); //adds the difference to the result list.

    }

    if (getSize(temp1) != getSize(temp2)) { //if the 2 lists are different in size then each of the remaining digits
        //will be added as is to the list by this function.

        moveDigitsSub(temp1, subtractList, digit1);
    }

    subtractList->data = 1;
    subtractList->data *= (n * temp2->data); //the sign of the result will depend on whether
    //the first is less than the second in abs value or vice verse. I.E
    //(-)6 - (-)5, 6 is greater than 5, so sign is 1 * -1 = -1

    filterList(subtractList); //removes any redundant zeros.
    deleteList(temp2); //frees list from memory
    deleteList(temp1);
    return subtractList;
}



/*
 * Internal Function to handle borrows in the subtraction of 2 numbers. Takes 2 lists and modifies
 * their values. I.E 62 - 54, the 2 will borrow from the 6 because 2 < 4.
 */

void borrow (struct node *l1, struct node *digit1) {
    struct node *p = digit1->previous;

    for (;p != l1; p = p->previous) {

        if (p->data > 0) {

            p->data--;
            digit1->data += 10; //adds 10 to the borrower
            break;
        }
        else {
            p->data += 9;
        }

    }
}


/*
 * Internal Function that handles the case when the lists are not equal in size
 * returns nothing, but modifies sumList.
 */

void moveDigitsSub (struct node *L, struct node* sumList, struct node* digit) {

    while (digit != L) {

        addFirst(sumList, digit->data);
        digit = digit->previous;
    }
}