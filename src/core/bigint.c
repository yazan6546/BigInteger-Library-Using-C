#include "bigint.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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

char* bigint_to_string(const BigInt* a) {

    if (a == NULL || a->head == NULL) {
        return NULL; // Invalid BigInt
    }

    struct node *L = a->head;
    char *result = malloc(1024); // Allocate enough space for the string
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    char *p = result;
    if (L->data == -1) {
        *p++ = '-'; // Add negative sign if needed
    }

    for (struct node *current = L->next; current != L; current = current->next) {
        *p++ = current->data + '0'; // Convert digit to character
    }
    *p = '\0'; // Null-terminate the string

    return result;
}

BigInt* bigint_create(const char *string) {

    BigInt *number = malloc(sizeof(BigInt));

    if (number == NULL) { //malloc fails
        return NULL;
    }

    number->head = NULL;
    number->head = makeEmpty(number->head);
    bool first = true;


    for (const char *p = string ; *p != '\0' ; p++) { // Iterate over the string
        if (!isdigit(*p) && (*p) != '-' ) {
            return NULL; // Invalid number
        }

        if (*p == '-' && first) {
            first = false;
            number->head->data = -1;
            continue;
        }
        if (*p == '-' && !first) {
            return NULL;
        }
        if (isdigit(*p) && first) {
            first = false;
            number->head->data = 1;
        }

        addLast(number->head, *p - '0');
    }

    return number;
}


int bigint_compare(const BigInt* a, const BigInt* b) {

    if (a == NULL || b == NULL || a->head == NULL || b->head == NULL) {
        return 0; // Invalid BigInt
    }

    filterList(a->head);
    filterList(b->head);

    int result = compare(a->head, b->head);
    return result;
}

BigInt* bigint_copy(const BigInt* number1) {
    struct node* number2 = copyList(number1->head);
    BigInt *copy = malloc(sizeof(BigInt));
    if (copy == NULL) {
        return NULL; // Memory allocation failed
    }
    copy->head = number2;
    return copy;
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

BigInt* bigint_subtract(const BigInt* a, const BigInt* b) {

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


BigInt* bigint_multiply(const BigInt* a, const BigInt* b) {

    BigInt *product_bigint = malloc(sizeof(BigInt));
    product_bigint->head = multiplyNumbers(a->head, b->head);

    return product_bigint;
}
