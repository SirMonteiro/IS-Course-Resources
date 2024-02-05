#include <stdio.h>

int input;
int numberLength = 0;
int res[64];

int main()
{
  printf("Number to convert to binary: \n");
  scanf("%i", &input);

  while (input > 0)
  {
    res[numberLength] = input % 2;
    input = input / 2;
    numberLength++;
  }

  for (numberLength--; numberLength >= 0; numberLength--)
  {
    printf("%i", res[numberLength]);
  }

  printf("\n");
  return 0;
}