#include <stdio.h>

int numBinary[9];

int main()
{

  numBinary[0] = 484 % 2;
  numBinary[1] = 484 / 2 % 2;
  numBinary[2] = 484 / 2 / 2 % 2;
  numBinary[3] = 484 / 2 / 2 / 2 % 2;
  numBinary[4] = 484 / 2 / 2 / 2 / 2 % 2;
  numBinary[5] = 484 / 2 / 2 / 2 / 2 / 2 % 2;
  numBinary[6] = 484 / 2 / 2 / 2 / 2 / 2 / 2 % 2;
  numBinary[7] = 484 / 2 / 2 / 2 / 2 / 2 / 2 / 2 % 2;
  numBinary[8] = 484 / 2 / 2 / 2 / 2 / 2 / 2 / 2 / 2 % 2;

  printf("%i", numBinary[8]);
  printf("%i", numBinary[7]);
  printf("%i", numBinary[6]);
  printf("%i", numBinary[5]);
  printf("%i", numBinary[4]);
  printf("%i", numBinary[3]);
  printf("%i", numBinary[2]);
  printf("%i", numBinary[1]);
  printf("%i", numBinary[0]);
  printf("\n");

  return 0;
}