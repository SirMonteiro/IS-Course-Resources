#include <stdio.h>
#include <time.h>

int fib(int n)
{
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fib(n - 1) + fib(n - 2);
}

int main()
{
  int n, fibn;
  double timeTaken = 0;
  scanf("%i", &n);
  clock_t t;
  for (int i = 0; i < n; i++)
  {
    t = clock();
    fibn = fib(i);
    t = clock() - t;
    timeTaken = ((double)t) / CLOCKS_PER_SEC;
    printf("%.3fs %i: %i\n", timeTaken, i, fibn);
  }
  // printf("%i %i\n", n, fib(n));
}
