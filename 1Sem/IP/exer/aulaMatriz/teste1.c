#include <stdio.h>

int main()
{
  int matriz[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  // printf("%i\n", sizeof(matriz) / sizeof(matriz[0]));
  // printf("%i\n", sizeof(matriz[0]) / sizeof(int));

  for (int i = 0; i < sizeof(matriz) / sizeof(matriz[0]); i++)
  {
    for (int j = 0; j < sizeof(matriz[0]) / sizeof(int); j++)
    {
      printf("%i\t", matriz[i][j]);
    }
    printf("\n");
  }

  return 0;
}