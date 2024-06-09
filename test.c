//
// Created by yazan on 6/9/2024.
//
#include "bigint.h"

int main () {

    BigInt *x = bigint_create("-23423");
    BigInt *y = bigint_create("128432423");

    BigInt *add = bigint_add(x, y);
    bigint_print(add, stdout);
}