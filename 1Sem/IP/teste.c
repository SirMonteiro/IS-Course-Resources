#include <stdio.h>

int variable;

int main()
{
  scanf("%d", &variable);

  // printf("%d", variable);

  printf("%i\n", variable);
  if (variable <= 0)
  {
    printf("enters if true");
  }
  else
  {
    printf("enters if false");
  }
  return 0;
}