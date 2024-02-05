#include <stdio.h>

int maior(int x, int y, int z)
{
  if (x > y && x > z)
  {
    return x;
  }
  else if (y > x && y > z)
  {
    return y;
  }
  return z;
}

int main()
{
  int x, y, z;

  printf("Entre com três inteiros:");

  scanf("%d %d %d", &x, &y, &z);

  // Inclua seu código.
  printf("%i\n", maior(x, y, z));

  return 0;
}
