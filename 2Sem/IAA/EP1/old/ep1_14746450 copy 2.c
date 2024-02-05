/*********************************************************************/
/**   ACH2002 - Introducao a Analise de Algoritmos                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 01 - Prof.Dra. Ariane Machado Lima                      **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/**   15/10/2023                                                    **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILENAME 256 // tamanho máximo de um nome de arquivo

int findMax(int expoente, int totalMatrixSize, FILE *file, int *result)
{
  int matrixSize = 1 << expoente;

  if (matrixSize == 2)
  {
    // printf("teste2 %d\n", totalMatrixSize / matrixSize);
    // printf("%d\n", totalMatrixSize / 2);

    // create matrix to use with the values read from file
    int **matrix = (int **)malloc(sizeof(int *) * totalMatrixSize);
    for (int i = 0; i < totalMatrixSize; i++)
    {
      matrix[i] = (int *)malloc(sizeof(int) * totalMatrixSize);
    }

    for (int i = 0; i < totalMatrixSize; i++)
    {
      for (int j = 0; j < totalMatrixSize; j++)
      {
        fscanf(file, "%1d", &matrix[i][j]);
      }
    }

    int auxBlack, auxWhite;
    for (int i = 0; i < totalMatrixSize; i = i + 2)
    {
      for (int j = 0; j < totalMatrixSize; j = j + 2)
      {
        auxBlack = result[expoente - 1];
        auxWhite = result[expoente];
        matrix[i][j] == 0 ? result[expoente - 1]++ : result[expoente]++;
        matrix[i][j + 1] == 0 ? result[expoente - 1]++ : result[expoente]++;
        matrix[i + 1][j] == 0 ? result[expoente - 1]++ : result[expoente]++;
        matrix[i + 1][j + 1] == 0 ? result[expoente - 1]++ : result[expoente]++;
        if (result[expoente - 1] - auxBlack == 4)
        {
          result[expoente + 1]++;
          result[expoente - 1] -= 4;
        }
        else if (result[expoente] - auxWhite == 4)
        {
          result[expoente + 2]++;
          result[expoente] -= 4;
        }
      }
    }
    free(matrix);
    return 1;
  }
  else
  {
    // printf("matrixSize: %d\n", matrixSize); // print the current matrix size
    findMax(expoente - 1, totalMatrixSize, file, result);
    printf("passou por aqui %d\n", matrixSize);
    // printf("passou por total %d\n", totalMatrixSize);
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Este programa exige dois argumentos: <número expoente de 2: 0 a 10> e <arquivo .txt>\n");
    exit(1);
  }

  // read first argment and sanitize it
  int expoente = atoi(argv[1]);
  if (expoente < 0 || expoente > 10)
  {
    printf("O expoente deve ser um número inteiro entre 0 e 10\n");
    exit(1);
  }
  int matrixSize = 1 << expoente;

  // read second argment and read the .txt file
  char filename[MAX_FILENAME] = "";
  strcpy(filename, argv[2]);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Não foi possível abrir o arquivo %s\n", filename);
    exit(1);
  }

  // printf("%d\n", matrixSize); // print the matrix size
  // printf("%s\n", filename);   // print the filename

  int *result = (int *)malloc(sizeof(int) * (expoente + 1) * 2);

  findMax(expoente, matrixSize, fp, result);

  for (int i = (expoente + 1); i > 0; i--)
  {
    printf("%dx%d %d %d\n", 1 << i - 1, 1 << i - 1, result[i * 2 - 1], result[i * 2 - 2]);
  }
  printf("teste |%d|, |%d|, |%d|, |%d|, |%d|, |%d|, |%d|, |%d|, |%d|, |%d|\n", result[0], result[1], result[2], result[3], result[4], result[5], result[6], result[7], result[8], result[9]);

  free(result);
  fclose(fp);
  return 0;
}