#ifndef PROJ_BIGINT_H
#define PROJ_BIGINT_H

#include "arithmetic/arithmetic.h"

typedef struct {
    struct node* head;
} BigInt;

// Function declarations for basic utility functions

/**
 * @brief Creates a BigInt from a string representation.
 * @param str The string representation of the big integer.
 * @return A pointer to the newly created BigInt, or NULL on failure.
 */
BigInt* bigint_create(char *string);

/**
 * @brief Frees the memory allocated for a BigInt.
 * @param a The BigInt to free.
 */
void bigint_free(BigInt* a);

/**
 * @brief Creates a copy of a BigInt.
 * @param a The BigInt to copy.
 * @return A pointer to the newly created copy of the BigInt, or NULL on failure.
 */
void bigint_copy(const BigInt* number1, const BigInt* number2);

/**
 * @brief Prints a BigInt to standard output.
 * @param number :  The BigInt to print.
 */
void bigint_print (const BigInt *number, FILE *q);

/**
 * @brief Compares two BigInts.
 * @param a The first BigInt.
 * @param b The second BigInt.
 * @return -1 if a < b, 0 if a == b, and 1 if a > b.
 */
int bigint_compare(const BigInt* a, const BigInt* b);

/**
 * @brief Converts a BigInt to a string representation.
 * @param a The BigInt to convert.
 * @return A newly allocated string representing the BigInt, or NULL on failure.
 */
char* bigint_to_string(const BigInt* a);


/**
 * @brief Adds two BigInts.
 * @param a The first BigInt.
 * @param b The second BigInt.
 * @return A pointer to the resulting BigInt after addition.
 */
BigInt* bigint_add(const BigInt* a, const BigInt* b);


/**
 * @brief Subtracts the second BigInt from the first BigInt.
 * @param a The first BigInt.
 * @param b The second BigInt.
 * @return A:  pointer to the resulting BigInt after subtraction.
 */
BigInt* bigint_subtract(const BigInt* a, const BigInt* b);


/**
 * @brief Multiplies two BigInts.
 * @param a The first BigInt.
 * @param b The second BigInt.
 * @return A pointer to the resulting BigInt after multiplication.
 */
BigInt* bigint_multiply(const BigInt* a, const BigInt* b);

/**
 * @brief Divides the first BigInt by the second BigInt.
 * @param a The first BigInt.
 * @param b The second BigInt.
 * @return A pointer to the resulting BigInt after division.
 */
BigInt* bigint_divide(const BigInt* a, const BigInt* b);

BigInt** bigint_divide_and_remainder(const BigInt* a, const BigInt* b);
BigInt* bigint_remainder(const BigInt *a, const BigInt *b);

#endif //PROJ_BIGINT_H
