# BigInt Library

## Overview

The BigInt Library is a C library for performing arithmetic operations on arbitrarily large integers. The library uses linked lists to manage the digits of big integers and includes modules for addition, subtraction, multiplication, and division.

## Program Structure
```
bigint_library/
├── Arithmetic/
│ ├── arithmetic.c
│ ├── arithmetic.h
│ ├── add.c
│ ├── sub.c
│ ├── division.c
│ └── mult.c
├── LinkedList/
│ ├── LinkedList.c
│ └── LinkedList.h
├── bigint.c
├── bigint.h
└── test.c
```


### `Arithmetic/` Directory

This directory contains the modules for arithmetic operations on BigInts:
- **`arithmetic.c`**: Core arithmetic functions.
- **`arithmetic.h`**: Header file for arithmetic functions.
- **`add.c`**: Addition operation implementation.
- **`sub.c`**: Subtraction operation implementation.
- **`division.c`**: Division operation implementation.
- **`mult.c`**: Multiplication operation implementation.

### `LinkedList/` Directory

This directory contains the modules for linked list operations:
- **`LinkedList.c`**: Implementation of linked list functions.
- **`LinkedList.h`**: Header file for linked list functions.

### Other Files

- **`bigint.c`**: Main implementation file for BigInt module, including creation, utilities, and encapsulated arithmetic operations.
- **`bigint.h`**: Header file for BigInt module.
- **`test.c`**: Test file to verify the functionality of the library.

## Installation

1. Clone the repository:
```sh
git clone https://github.com/your_username/bigint_library.git
```
2. Navigate to the repository directory:

```sh
cd bigint_library
```

3. Compile the library and test program:
```sh
gcc -o test test.c Arithmetic/arithmetic.c Arithmetic/add.c Arithmetic/sub.c Arithmetic/division.c Arithmetic/mult.c LinkedList/LinkedList.c bigint.c
```

## Usage 
Include the bigint.h and relevant modules in your project to use the BigInt library functions. Here is a simple example of how to use the library:

```C
#include <stdio.h>
#include "bigint.h"

int main() {
    BigInt* a = bigint_from_string("12345678901234567890");
    BigInt* b = bigint_from_string("98765432109876543210");
    
    BigInt* sum = bigint_add(a, b);
    BigInt* diff = bigint_subtract(a, b);
    BigInt* product = bigint_multiply(a, b);
    BigInt* quotient = bigint_divide(a, b);

    bigint_print(sum); // Print the sum
    bigint_print(diff); // Print the difference
    bigint_print(product); // Print the product
    bigint_print(quotient); // Print the quotient

    // Free the allocated memory
    bigint_free(a);
    bigint_free(b);
    bigint_free(sum);
    bigint_free(diff);
    bigint_free(product);
    bigint_free(quotient);

    return 0;
}
```

## Function Descriptions

### BigInt Utility Functions

- **`BigInt* bigint_create(char *string);`**
  - **Description:** Creates a `BigInt` from a string representation.
  - **Parameters:** 
    - `str` - The string representation of the big integer.
  - **Returns:** A pointer to the newly created `BigInt`, or `NULL` on failure.

- **`void bigint_free(BigInt* a);`**
  - **Description:** Frees the memory allocated for a `BigInt`.
  - **Parameters:** 
    - `a` - The `BigInt` to free.

- **`void bigint_copy(const BigInt* number1, const BigInt* number2);`**
  - **Description:** Creates a copy of a `BigInt`.
  - **Parameters:** 
    - `number1` - The `BigInt` to copy from.
    - `number2` - The `BigInt` to copy to.

- **`void bigint_print(const BigInt *number, FILE *q);`**
  - **Description:** Prints a `BigInt` to standard output.
  - **Parameters:** 
    - `number` - The `BigInt` to print.
    - `q` - The file stream to print to.

- **`int bigint_compare(const BigInt* a, const BigInt* b);`**
  - **Description:** Compares two `BigInts`.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** `-1` if `a < b`, `0` if `a == b`, and `1` if `a > b`.

- **`char* bigint_to_string(const BigInt* a);`**
  - **Description:** Converts a `BigInt` to a string representation.
  - **Parameters:** 
    - `a` - The `BigInt` to convert.
  - **Returns:** A newly allocated string representing the `BigInt`, or `NULL` on failure.

### BigInt Arithmetic Functions

- **`BigInt* bigint_add(const BigInt* a, const BigInt* b);`**
  - **Description:** Adds two `BigInts`.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** A pointer to the resulting `BigInt` after addition.

- **`BigInt* bigint_subtract(const BigInt* a, const BigInt* b);`**
  - **Description:** Subtracts the second `BigInt` from the first `BigInt`.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** A pointer to the resulting `BigInt` after subtraction.

- **`BigInt* bigint_multiply(const BigInt* a, const BigInt* b);`**
  - **Description:** Multiplies two `BigInts`.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** A pointer to the resulting `BigInt` after multiplication.

- **`BigInt* bigint_divide(const BigInt* a, const BigInt* b);`**
  - **Description:** Divides the first `BigInt` by the second `BigInt`.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** A pointer to the resulting `BigInt` after division.

- **`BigInt** bigint_divide_and_remainder(const BigInt* a, const BigInt* b);`**
  - **Description:** Divides the first `BigInt` by the second `BigInt` and provides both quotient and remainder.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** A pointer to an array containing the quotient and remainder `BigInts`.

- **`BigInt* bigint_remainder(const BigInt *a, const BigInt *b);`**
  - **Description:** Computes the remainder of the division of the first `BigInt` by the second `BigInt`.
  - **Parameters:** 
    - `a` - The first `BigInt`.
    - `b` - The second `BigInt`.
  - **Returns:** A pointer to the resulting `BigInt` after computing the remainder.

## Testing
Run the provided test program to verify the functionality of the library:
```sh
./test
```
