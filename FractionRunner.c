/******************************
 *  FractionRunner.c - A fraction-math lab
 *
 *  name: Aaron Jordan
 *  date: 2/18/20
 *  course: CSCI 356
 *  version: 1.0
 *  email: jajorda3@coastal.edu
 *****************************/

#include"FractionRunner.h"

int main(int argc, char** argv) {
  
  int user = 8; // prevent infinite recursion
  Fraction fraction1;
  Fraction fraction2;

  // initialize zero-fractions
  fraction1.numerator = 0;
  fraction2.numerator = 0;
  fraction2.denominator = 1;
  fraction1.denominator = 1;

  do {
    printGreeting();
    user = getUserInput();

    switch (user){
    case 1:
      setfrac(&fraction1);
      break;
    case 2:
      setfrac(&fraction2);
      break;
    case 3:
      addf(&fraction1, &fraction2);
      break;
    case 4:
      subf(&fraction1, &fraction2);
      break;
    case 5:
      multf(&fraction1, &fraction2);
      break;
    case 6:
      printmf(&fraction1, &fraction2);
      break;
    case 7:
      compf(&fraction1, &fraction2);
      break;
    case 8:
      printf("Thanks for using the Fraction Runner. Have a great day!\n\n");
      break;
    default:
       printf("Woah. That's not valid input.\n\n");
    }

  } while (user!=8);

  return 0;
}

void printGreeting() {
  printf("*************************************************************************\n* Enter 1 to set the numerator and denominator of the first fraction    *\n* Enter 2 to set the numerator and denominator of the second fraction   *\n* Enter 3 to add the two fractions (result assigned to fraction 1)      *\n* Enter 4 to subtract the two fractions (result assigned to fraction 1) *\n* Enter 5 to multiply the two fractions (result assigned to fraction 1) *\n* Enter 6 to print out the first and second fractions to the console    *\n* Enter 7 to compare the two fractions for equality                     *\n* Enter 8 to quit the fraction tester                                   *\n*************************************************************************\n\n"); 
}

int getUserInput() {
  printf("selection: ");
  int s = 0;
  scanf("%i", &s);
  return s;
}

bool setfrac(Fraction* f) {
  int n = 0;
  int d = 1; // not zero obviously

  //get input
  printf("Please enter the numerator and denominator separated by a space: ");
  scanf("%i %i", &n, &d);

  if(d==0) {
    printf("The denominator cannot be zero. Please choose different values.\n");
    printf("Enter the numerator and denominator separated by a space: ");
    scanf("%i %i", &n, &d);
  }

  f->numerator = n;
  f->denominator = d;

  printf("The fraction is now: ");
  printfrac(f);
  printf("\n\n");

  return true;
}

void printfrac(Fraction* f) {
  printf("%i/%i", f->numerator, f->denominator);
}

bool quickGCD(Fraction* f) {
  bool sign = ((f->numerator < 0) != (f->denominator < 0)) ? true : false;
  // remember if we started with a negative fraction
  f->numerator = (f->numerator < 0) ? -(f->numerator) : f->numerator;
  f->denominator = (f->denominator < 0) ? -(f->denominator) : f->denominator;
  
  int gcd[2] = {f->numerator, f->denominator};

  if(f->numerator > 0) {
    // numerator is bound on [0, inf)
    while ( gcd[0] != gcd[1] ) {
      if ( gcd[0] > gcd[1] )
        gcd[0] -= gcd[1];
      else
        gcd[1] -=gcd[0];
    }
  } else {
    gcd[0] = 1; // where numerator is zero, default gcd to 1
  }
  // gcd will be stored in both gcd[0] and [1]

  f->numerator /= gcd[0];
  f->denominator /= gcd[1];
  f->numerator *= (sign) ? -1 : 1;

  if(gcd[0] == 1) return false;
  return true;

}

bool addf(Fraction* f1, Fraction* f2) {
  // add, store in f1
  printfrac(f1);
  printf(" + ");
  printfrac(f2);
  printf(" = ");

  // get common denominator - requires swap variable 
  int tempDen = f1->denominator;
  f1->numerator *= f2->denominator;
  f1->denominator *= f2->denominator;
  f2->numerator *= tempDen;
  f2->denominator *= tempDen;

  // add into f1
  f1->numerator += f2->numerator;

  // simplify fractions
  quickGCD(f1);
  quickGCD(f2);

  // print result
  printfrac(f1);
  printf("\n\n");

  return true; 
}

bool subf(Fraction* f1, Fraction* f2) {
  // subtract, store in f1
  printfrac(f1);
  printf(" - ");
  printfrac(f2);
  printf(" = ");

  // get common denominator - requires swap variable 
  int tempDen = f1->denominator;
  f1->numerator *= f2->denominator;
  f1->denominator *= f2->denominator;
  f2->numerator *= tempDen;
  f2->denominator *= tempDen;

  // add into f1
  f1->numerator -= f2->numerator;

  // simplify fractions
  quickGCD(f1);
  quickGCD(f2);

  // print result
  printfrac(f1);
  printf("\n\n");

  return true; 
}

bool multf(Fraction* f1, Fraction* f2) {
  // mult, store in f1
  printfrac(f1);
  printf(" * ");
  printfrac(f2);
  printf(" = ");

  // multiply straight across
  f1->numerator *= f2->numerator;
  f1->denominator *= f2->denominator;
 
  // simplify fractions
  quickGCD(f1);
  quickGCD(f2);

  // print result
  printfrac(f1);
  printf("\n\n");

  return true; 
}

void printmf(Fraction* f1, Fraction* f2) {
  printf("The stored fractions are currently\nFraction 1: ");
  printfrac(f1);
  printf("\nFraction 2: ");
  printfrac(f2);
  printf("\n\n");
}

bool compf(Fraction* f1, Fraction* f2) {
  // simplify fractions
  quickGCD(f1);
  quickGCD(f2);

  // directly compare equality
  bool eq = ((f1->numerator==f2->numerator)&&(f1->denominator==f2->denominator));

  if (eq) {
    printf("The two fractions are equivalent. Both are equal to ");
    printfrac(f1);
    printf(".\n\n");
    return true;
  } else {
    printf("The two fractions are not equivalent.\n");
    printf("\033[1;31m"); //bold red
    printfrac(f1);
    printf("\033[0m"); // plain
    printf(" != ");
    printfrac(f2);
    printf("\n\n");
  }

  return false;
}

