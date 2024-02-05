#include <stdio.h>

long long int fatorial(long long int n)
{
  if (n == 0)
    return 1;
  return n * fatorial(n - 1);
}

int main()
{
  int n;
  scanf("%i", &n);
  printf("%i %i\n", n, fatorial(n));
}
