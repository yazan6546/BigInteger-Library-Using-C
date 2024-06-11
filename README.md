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

## Testing
Run the provided test program to verify the functionality of the library:
```sh
./test
```
