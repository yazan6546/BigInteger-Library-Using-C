/*
 * Name = yazan AboAlown
 * ID = 121045
 * Section : 3
 */

#include <ctype.h>
#include "LinkedList/LinkedList.h"

void showMenu ();
struct node** readFile1 (int *size);
void delete_array_linkedLists(struct node **array, int length);

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
        printNumber(array[i], stdout);
        printf("   ");
    }


    printf("\n");

    while (input != 5) {

        showMenu();
        scanf("%d", &input);

        if (input >= 1 && input <= 4) {
            printf("Choose 2 numbers that you want to perform the selected operation on. \n");
            scanf("%d%d", &first, &second);
        }
        switch (input) {

            case 1:
                result = addNumbers(array[first - 1], array[second - 1]);
                break;

            case 2:
                result = subtractNumbers(array[first - 1], array[second - 1]);
                break;

            case 3:
                result = multiplyNumbers(array[first - 1], array[second - 1]);
                break;

            case 4: {
                divisionAndRemainder = divideAndRemainder(array[first - 1], array[second - 1]);
                result = divisionAndRemainder[0];
                break;
            }

            case 5:
                printf("Program terminated.\n");
                break;

            default:
                printf("Enter a valid operation!");
        }

        if (input >= 1 && input <= 4) {

            printNumber(array[first - 1], stdout);
            printf(" %c ", op[input - 1]);
            printNumber(array[second - 1], stdout);
            printf(" = ");
            printNumber(result, stdout);
            printf("\n");

            printNumber(array[first - 1], output);
            fprintf(output, " %c ", op[input - 1]);
            printNumber(array[second - 1], output);
            fprintf(output, " = ");
            printNumber(result, output);
            fprintf(output, "\n");

            deleteList(result);
        }
        //handles the mod in division
        if (input == 4) {

            printNumber(array[first - 1], stdout);
            printf(" mod ");
            printNumber(array[second - 1], stdout);
            printf(" = ");
            printNumber(divisionAndRemainder[1], stdout);
            printf("\n");

            printNumber(array[first - 1], output);
            fprintf(output, " mod ");
            printNumber(array[second - 1], output);
            fprintf(output, " = ");
            printNumber(divisionAndRemainder[1], output);
            fprintf(output, "\n");

            free(divisionAndRemainder);

        }


    }
    delete_array_linkedLists(array, size);
    fclose(output);
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

    *size = 0;
    FILE *p = fopen("input.txt", "r");
    FILE *q = fopen("input.txt", "r");

    if (p == NULL || q == NULL) { //Checks if the files are opened successfully

        printf("Error opening the file\n");
    }

    /*
     * This while loop counts the numbers in the file just to specify
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
         * only when a negative sign or a digit are encountered
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

void delete_array_linkedLists(struct node **array, int length) {

    for (int i = 0; i<length; i++) {
        deleteList(array[i]);
    }

    free(array);
}
