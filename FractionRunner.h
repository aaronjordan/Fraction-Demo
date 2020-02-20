/******************************
 *  FractionRunner.h - A fraction-math lab
 *
 *  name: Aaron Jordan
 *  date: 2/18/20
 *  course: CSCI 356
 *  version: 1.0
 *  email: jajorda3@coastal.edu
 *****************************/
#include<stdio.h>
#include<stdbool.h>

typedef struct {
   int numerator;
   int denominator;
} Fraction;

void printGreeting();
// print the menu

void printfrac(Fraction *);
// print the given fraction. "n/d" no newline.

int getUserInput();
// return int selection

bool setfrac(Fraction *);
// set specified fraction, return true if successful

bool addf(Fraction *, Fraction *);
// add specified fractions, return true if successful

bool subf(Fraction *, Fraction *);
// subtract specified fractions, return true if successful

bool multf(Fraction *, Fraction *);
// multiply specified fractions, return true if successful

void printmf(Fraction *, Fraction *);
// print specified fractions to stdout - menu selection

bool compf(Fraction *, Fraction *);
// compare equality of specified fractions, return true if equality holds

bool quickGCD(Fraction *);
// find the greatest common denominator and simplify the referenced fraction
// return true if simplifies, false if no simplification possible
