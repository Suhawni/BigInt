#ifndef BigInteger_h
#define BigInteger_h
#include<stdio.h> 
struct BigInteger{
    int sign;  // 0 for positive and 1 for negative 
    int *data;
    int len; // number of digits in the bigint
};
//FUNCTION DECLARATIONS
struct BigInteger initialise(char* str);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
void display(struct BigInteger b);
int compare(struct BigInteger a,struct BigInteger b);
struct BigInteger add(struct BigInteger a,struct BigInteger b);
struct BigInteger addition(struct BigInteger a,struct BigInteger b);
struct BigInteger subtraction(struct BigInteger a,struct BigInteger b);
struct BigInteger mul(struct BigInteger a,struct BigInteger b);
#endif