#include <stdio.h>

float maior(float x, float y, float z)
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
  float x, y, z;

  printf("Entre com três flutuantes:");

  scanf("%f %f %f", &x, &y, &z);

  // Inclua seu código.
  printf("%f\n", maior(x, y, z));

  return 0;
}
