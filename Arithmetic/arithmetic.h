#ifndef PROJ_ARITHMETIC_H
#define PROJ_ARITHMETIC_H

#include "../LinkedList/LinkedList.h"


struct node* addNumbers (struct node *l1, struct node *l2);
void moveDigitsSum (struct node* L, struct node* sumList, struct node* digit, int carry);

struct node* subtractNumbers (struct node *l1 , struct node *l2);
void moveDigitsSub (struct node *L, struct node* sumList, struct node* digit);
void borrow (struct node *l1, struct node *digit1);

struct node* multiplyListByNumber (struct node *l1, int number);
struct node* multiplyNumbers (struct node *l1, struct node *l2);

struct node **divideAndRemainder (struct node *l1, struct node *l2);
int divisionSubtract (struct node *l1, struct node *l2);

void filterList (struct node *l1);
int compare (struct node *l1, struct node *l2);


#endif //PROJ_ARITHMETIC_H
