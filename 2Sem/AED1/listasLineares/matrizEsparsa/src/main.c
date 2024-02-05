#include "matrizesparsa.c"

#define COL 10
#define LIN 10
 
int main()
{
  MATRIZ *matriz = (MATRIZ *)malloc(sizeof(MATRIZ));
  inicializar(matriz, LIN, COL, 0);

  int **m = (int **)malloc(sizeof(int *) * LIN);
  for (int i = 0; i < LIN; i++)
  {
    m[i] = (int *)malloc(sizeof(int) * COL);
    for (int j = 0; j < COL; j++)
    {
      m[i][j] = 0;
    }
  }

  m[0][0] = 10;
  m[1][2] = 12;
  m[5][5] = 55;
  m[9][9] = 99;

  for (int i = 0; i < LIN; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      if (m[i][j] != 0)
      {
        atribuir(matriz, i, j, m[i][j]);
      }
    }
  }

  // atribuir(matriz, 0, 0, 10);
  // atribuir(matriz, 5, 5, 50);
  // atribuir(matriz, 9, 9, 90);

  exibir(matriz);

  printf("\nO valor é: %d\n", valorCelula(matriz, 0, 1));
  printf("Zeros na matriz: %d\n", countZeros(matriz));

  // zerarDiagPrincipal(matriz);

  // zerarLinha(matriz, 5);
  zerarColuna(matriz, 5);

  exibirLinha(matriz, 0);
  exibirLinha(matriz, 1);
  exibirLinha(matriz, 2);
  exibirLinha(matriz, 3);
  exibirLinha(matriz, 4);
  exibirLinha(matriz, 5);
  exibirLinha(matriz, 6);
  exibirLinha(matriz, 7);
  exibirLinha(matriz, 8);
  exibirLinha(matriz, 9);

  printf("Zeros na matriz: %d\n", countZeros(matriz));

  return 0;
}
