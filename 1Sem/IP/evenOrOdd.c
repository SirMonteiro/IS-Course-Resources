#include <stdio.h>

// Test if a number is Even or Odd

int evenOrOdd(int number) { return (number % 2); }
int main()
{
  int a, b;
  printf("Insert two number to analyze if it's Even or Odd: ");
  scanf("%d, %d", &a, &b);
  printf("The number A is: %s\n", evenOrOdd(a) ? "Odd" : "Even");
  printf("The number B is: %s\n", evenOrOdd(b) ? "Odd" : "Even");
  return 0;
}