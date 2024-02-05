#include <stdio.h>

typedef struct Struct
{
  int var1;
  int var2[4];
} structTest;

int main()
{
  structTest st1;
  st1.var1 = 1;
  printf("%i\n", st1.var1);

  st1.var2[0] = 2;

  printf("%i\n", st1.var2[0]);
  return 0;
}