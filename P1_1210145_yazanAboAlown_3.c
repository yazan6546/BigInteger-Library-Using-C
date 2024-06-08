/*
 * Name = yazan AboAlown
 * ID = 121045
 * Section : 3
 */

#include <ctype.h>
#include "LinkedList/LinkedList.h"

void showMenu ();
void printNumber_file (struct node *L, FILE *q);
struct node** readFile1 (int *size);
struct node* addNumbers (struct node *l1, struct node *l2);
struct node* subtractNumbers (struct node *l1 , struct node *l2);
struct node **divideAndRemainder (struct node *l1, struct node *l2);
void moveDigitsSum (struct node* L, struct node* sumList, struct node* digit, int carry);
void moveDigitsSub (struct node *L, struct node* sumList, struct node* digit);
struct node* multiplyListByNumber (struct node *l1, int number);
struct node* multiplyNumbers (struct node *l1, struct node *l2);
int compare (struct node *l1, struct node *l2);
void borrow (struct node *l1, struct node *digit1);
void filterList (struct node *l1);
struct node * createZero();
void printNumber(struct node *L);
int divisionSubtract (struct node *l1, struct node *l2);

int main() {


    FILE* output = fopen("output.txt", "a");

    if (output == NULL) { //checks if the file is opened successfully

        printf("Error opening the file!\n");
        exit(1);
    }

    printf("\n");

    int size = 0;
    int input = 0, first, second;
    struct node *result;
    struct node **divisionAndRemainder;
    struct node **array = readFile1(&size); //gets the set of lists contained in the input file

    char op[] = {'+', '-', '*', '/'};

    for (int i = 0; i < size; i++) {

        if (i % 8 == 0) { //prints 8 numbers in a line
            printf("\n");
        }

        printf("%d) ", i+1);
        printNumber(array[i]);
        printf("   ");
    }


    printf("\n");

    for (;input != 5;) {

        showMenu();
        scanf("%d", &input);

        if (input >= 1 && input <= 4) {
            printf("Choose 2 numbers that you want to perform the selected operation on. \n");
            scanf("%d%d", &first, &second);
        }
        switch (input) {

            case 1:
                result = addNumbers(array[first-1], array[second-1]);
                break;

            case 2:
                result = subtractNumbers(array[first-1], array[second-1]);
                break;

            case 3:
                result = multiplyNumbers(array[first-1], array[second-1]);
                break;

            case 4:

                divisionAndRemainder = divideAndRemainder(array[first-1], array[second-1]);
                break;

            case 5:
                printf("Program terminated.\n");
                break;

            default:
                printf("Enter a valid operation!");
        }

        if (input >= 1 && input <= 3) {

            printNumber(array[first - 1]);
            printf(" %c ", op[input - 1]);
            printNumber(array[second - 1]);
            printf(" = ");
            printNumber(result);
            printf("\n");

            printNumber_file(array[first - 1], output);
            fprintf(output, " %c ", op[input - 1]);
            printNumber_file(array[second - 1], output);
            fprintf(output, " = ");
            printNumber_file(result, output);
            fprintf(output, "\n");

            deleteList(result);
        }
        //handles the division case
        else if (input == 4) {

            printNumber(array[first - 1]);
            printf(" %c ", op[input - 1]);
            printNumber(array[second - 1]);
            printf(" = ");
            printNumber(divisionAndRemainder[0]);
            printf("\n");

            printNumber_file(array[first - 1], output);
            fprintf(output, " %c ", op[input - 1]);
            printNumber_file(array[second - 1], output);
            fprintf(output, " = ");
            printNumber_file(divisionAndRemainder[0], output);
            fprintf(output, "\n");

            printNumber(array[first - 1]);
            printf(" mod ", op[input - 1]);
            printNumber(array[second - 1]);
            printf(" = ");
            printNumber(divisionAndRemainder[1]);
            printf("\n");

            printNumber_file(array[first - 1], output);
            fprintf(output, " mod ");
            printNumber_file(array[second - 1], output);
            fprintf(output, " = ");
            printNumber_file(divisionAndRemainder[1], output);
            fprintf(output, "\n");

            deleteList(divisionAndRemainder[0]);
            deleteList(divisionAndRemainder[1]);
            free(divisionAndRemainder);

        }


    }
    fclose(output);
}

/*
 * Function to print the number represented by the linked list in a file
 * supplied by the parameter. Takes a head as the first input and the file
 * pointer for the second input.
 */

void printNumber_file (struct node *L, FILE *q) {

    if (L->data == -1) {      //checks for the negative in the head and prints it

        fprintf(q, "-");
    }
    for (struct node *p = L->next; p != L; p = p->next) { //prints each digit in the linked list
        fprintf(q, "%d", p->data);
    }
}

/*
 * Function to display the menu. Meant to be called in the main
 */

void showMenu () {
    printf("\n\n***----------------BigIntegers Calculator----------------------*\n\n\n");
    printf("Choose one of these options for the listed numbers.\n"
           "1. Add two numbers.\n"
           "2. Subtract two numbers.\n"
           "3. Multiply two numbers.\n"
           "4. Divide two numbers\n"
           "5. Exit program\n\n");
}


/*
 * Function to read a set of numbers from a file and return
 * them as an array of heads. Saves them in a linked list
 * one digit for each node, if a negative sign is read, then it will be
 * saved in the head. -1 if negative, 1 if positive. Takes an int pointer as
 * parameter just to specify the size of the array when called in main. This function
 * assumes that the numbers are arranged each one at a line.
 */

struct node** readFile1 (int *size) {

    int n;

    FILE *p = fopen("input.txt", "r");
    FILE *q = fopen("input.txt", "r");

    if (p == NULL || q == NULL) { //Checks if the files are opened successfully

        printf("Error opening the file\n");
    }

    /*
     * This while loop counts the numbers in the file just so as to specify
     * the size of the array to be returned. It uses getc to read the characters
     * one by one, and counts the numbers by seeing how many new line characters are
     * in the file.
     */

    while ((n = getc(p)) != EOF) {
        if (n == '\n') {
            (*size)++;
        }
    }

    (*size)++;
    fclose(p);

    struct node **r = malloc( sizeof(struct node*) * (*size)); //allocates space in memory for the array of heads

    if (r == NULL) { //exits program if allocation fails

        printf("Out of memory!\n");
        exit(1);
    }

    /*
     * This for loop saves number each number read in the file in the array
     */
    for (int i = 0;i<(*size);i++) {

        r[i] = NULL;
        r[i] = makeEmpty(r[i]);


        /*
         * skips any non digit character in the file, and exits loop
         * only when the negative sign is encountered
         */

        while (!isdigit(n = getc(q))) {
            if (n == '-') {
                break;
            }
        }

        if (n == '-') { //puts -1 in the head when negative sign is read
            r[i]->data = -1;
        }
        else if (isdigit(n)) { //puts 1 in the head if no negative sign is encountered

            r[i]->data = 1;
            addLast(r[i], n - '0');
        }

        /*
         * reads characters from the file one by one and stops either when a non digit character is encountered
         * or when reaching the end of file
         */

        while (isdigit(n = getc(q)) && n != EOF) {

            addLast(r[i], n - '0'); //adds the number to the list and converts from ascii code to int
        }
        filterList(r[i]); //removes any leading zeros from the list as they are of no effect.
    }
    fclose(q);

    return r;

}


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

    if (n < 0) { //swaps both lists if the first is less than the second and inverts the sign after. I.E 5-6 = -(6-5).
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
 * Internal Function to compare 2 lists of numbers. Takes 2 lists as input and
 * returns an int. 1 is l1 > l2, 0 if l1 == l2, -1 if l1 < l2.
 */

int compare (struct node *l1, struct node *l2) {

    int s1, s2;

    s1 = getSize(l1);
    s2 = getSize(l2);


    if (s1 > s2) {
        return 1;
    }
    else if (s1 < s2) {
        return -1;
    }

    if (l1->next->isHead || l2->next->isHead) {
        return 0;
    }

    else if ((l1->next->data > l2->next->data)) {
        return 1;
    }
    else if ((l1->next->data < l2->next->data)) {

        return -1;
    }
    else {
        return compare(l1->next, l2->next);
    }
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
 * Function that takes 2 lists of numbers as input and returns
 * an array containing their division and remainder.
 */

struct node **divideAndRemainder (struct node *l1, struct node *l2) {

    int tempSign1 = l1->data;
    int tempSign2 = l2->data;

    struct node **array = malloc(2 * sizeof(struct node*)); //creates an array of 2 nodes

    struct node *division = NULL;
    division = makeEmpty(division);

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
 * Linked list prototype that returns a list representing a zero.
 */
struct node * createZero() {

    struct node *L = NULL;
    L = makeEmpty(L);
    L->data = 1;
    addFirst(L,0);

    return L;
}

/*
 * Function that prints the contents of a linked list of integers, and
 * takes into account the sign digit that is in the head. -1 if negative
 * and 1 if positive.
 */

void printNumber(struct node *L) {

    if (L->data == -1) {
        printf("-");
    }
    printList(L); //prints the contents of the list
}
