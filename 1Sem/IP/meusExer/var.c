#include <stdio.h>

int main()
{
  // code to sum two numbers and calculte the average with 3 decimal places
  float num1, num2, sum, avg;
  printf("Enter first number: ");
  scanf("%f", &num1);
  printf("Enter second number: ");
  scanf("%f", &num2);
  sum = num1 + num2;
  avg = sum / 2.0;
  printf("The average of %.2f and %.2f is %.3f", num1, num2, avg);
  return 0;
}