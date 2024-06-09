#include "bigint.h"

void bigint_print (const BigInt *number, FILE *q) {

    if (number == NULL) {
        printf("Invalid object.");
        return;
    }
    struct node *L = number->head;
    if (L->data == -1) {
        fprintf(q, "-");
    }
    printList(L, q); //prints the contents of the list
}

BigInt* bigint_create(char *string) {

    BigInt *number = malloc(sizeof(BigInt));
    number->head = NULL;
    number->head = makeEmpty(number->head);
    bool first = true;
    if (number == NULL) { //malloc fails
        return NULL;
    }

    for (char *p = string ; *p != '\0' ; p++) { // Iterate over the string
        if (!isdigit(*p) && (*p) != '-' ) {
            return NULL; // Invalid number
        }

        if (*p == '-' && first) {
            first = false;
            number->head->data = -1;
            continue;
        }

        else if (*p == '-' && !first) {
            return NULL;
        }

        else if (isdigit(*p) && first) {
            first = false;
            number->head->data = 1;
        }

        addLast(number->head, *p - '0');
    }

    return number;
}

void bigint_copy(const BigInt* number1, const BigInt* number2) {
    copyList(number1->head, number2->head);
}

void bigint_free(BigInt* a) {
    deleteList(a->head);
    free(a);
}

BigInt* bigint_add(const BigInt* a, const BigInt* b) {

    BigInt *sum_bigint = malloc(sizeof(BigInt));
    sum_bigint->head = addNumbers(a->head, b->head);

    return sum_bigint;
}

BigInt* bigint_sub(const BigInt* a, const BigInt* b) {

    BigInt *sub_bigint = malloc(sizeof(BigInt));
    sub_bigint->head = subtractNumbers(a->head, b->head);

    return sub_bigint;
}

BigInt** bigint_divide_and_remainder(const BigInt* a, const BigInt* b) {

    BigInt **array = malloc(2 * sizeof(BigInt*));
    array[0] = malloc(sizeof(BigInt));
    array[1] = malloc(sizeof(BigInt));

    struct node** results = divideAndRemainder(a->head, b->head);
    array[0]->head = results[0];
    array[1]->head = results[1];

    return array;
}

BigInt* bigint_divide(const BigInt *a, const BigInt *b) {

    BigInt **results = bigint_divide_and_remainder(a, b);
    bigint_free(results[1]);
    BigInt* division = results[0];
    free(results);

    return division;
}

BigInt* bigint_remainder(const BigInt *a, const BigInt *b) {

    BigInt **results = bigint_divide_and_remainder(a, b);
    bigint_free(results[0]);
    BigInt* remainder = results[1];
    free(results);

    return remainder;
}
