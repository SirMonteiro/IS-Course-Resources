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
#include <string.h>

#define MAX_FILENAME 256 // max length of filename

/* Recursive function that receives a base 2 exponent, a matrix,
 * the matrix size and a result matrix to store the maxx of a color from matrix
 */
int findMax(int exponent, int **matrix, int totalExponent, int aux[2], int **result)
{
  if (exponent == 0)
  {
    if (exponent == totalExponent)
    {
      if (matrix[0][0])
        result[exponent][1]++;
      else
        result[exponent][0]++;
    }
    return matrix[aux[0]][aux[1]];
  }
  int toCompare[4];
  toCompare[0] = findMax(exponent - 1, matrix, totalExponent, aux, result);
  aux[0] += (1 << exponent) / 2;
  toCompare[1] = findMax(exponent - 1, matrix, totalExponent, aux, result);
  aux[0] -= (1 << exponent) / 2;
  aux[1] += (1 << exponent) / 2;
  toCompare[2] = findMax(exponent - 1, matrix, totalExponent, aux, result);
  aux[0] += (1 << exponent) / 2;
  toCompare[3] = findMax(exponent - 1, matrix, totalExponent, aux, result);
  aux[0] -= (1 << exponent) / 2;
  aux[1] -= (1 << exponent) / 2;

  int maxx = 0;
  if (exponent == totalExponent)
    maxx = 1;

  if (toCompare[0] == 0 && toCompare[1] == 0 && toCompare[2] == 0 && toCompare[3] == 0)
  {
    if (maxx)
      result[exponent][0]++;
    return 0;
  }
  if (toCompare[0] == 1 && toCompare[1] == 1 && toCompare[2] == 1 && toCompare[3] == 1)
  {
    if (maxx)
      result[exponent][1]++;
    return 1;
  }
  if (toCompare[0] == 0)
    result[exponent - 1][0]++;
  else if (toCompare[0] == 1)
    result[exponent - 1][1]++;
  if (toCompare[1] == 0)
    result[exponent - 1][0]++;
  else if (toCompare[1] == 1)
    result[exponent - 1][1]++;
  if (toCompare[2] == 0)
    result[exponent - 1][0]++;
  else if (toCompare[2] == 1)
    result[exponent - 1][1]++;
  if (toCompare[3] == 0)
    result[exponent - 1][0]++;
  else if (toCompare[3] == 1)
    result[exponent - 1][1]++;

  return -1;
}

int main(int argc, char *argv[])
{
  // check if the number of arguments is correct
  if (argc != 3)
  {
    printf("Este programa exige dois argumentos: <número expoente de 2: 0 a 10> e <arquivo .txt>\n");
    exit(1);
  }

  // read first argment and sanitize it
  int exponent = atoi(argv[1]);
  if (exponent < 0 || exponent > 10)
  {
    printf("O exponent deve ser um número inteiro entre 0 e 10\n");
    exit(1);
  }
  // calculate the matrix size with base 2 exponent
  int matrixSize = 1 << exponent;

  // read second argment and read the .txt file
  char filename[MAX_FILENAME] = "";
  strcpy(filename, argv[2]);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Não foi possível abrir o arquivo %s\n", filename);
    exit(1);
  }

  // create matrix to use with the values read from file
  int **matrix = (int **)malloc(sizeof(int *) * matrixSize);
  for (int i = 0; i < matrixSize; i++)
  {
    matrix[i] = (int *)malloc(sizeof(int) * matrixSize);
  }

  for (int i = 0; i < matrixSize; i++)
  {
    for (int j = 0; j < matrixSize; j++)
    {
      fscanf(fp, "%1d", &matrix[i][j]);
    }
  }

  // printf("%d\n", matrixSize); // print the matrix size
  // printf("%s\n", filename);   // print the filename

  // alloc memory for result matrix
  int **result = (int **)malloc(sizeof(int *) * (exponent + 1));
  for (int i = 0; i < (exponent + 1); i++)
  {
    result[i] = (int *)malloc(sizeof(int) * 2);
    result[i][0] = 0;
    result[i][1] = 0;
  }

  int aux[2] = {0, 0};

  // call recursive function
  findMax(exponent, matrix, exponent, aux, result);

  // create file to write the result
  FILE *fpResult = fopen("saida.txt", "w");
  if (fpResult == NULL)
  {
    printf("Não foi possível criar o arquivo saida.txt\n");
    exit(1);
  }

  // print result
  for (int i = exponent; i >= 0; i--)
  {
    printf("%dx%d %d %d\n", 1 << i, 1 << i, result[i][1], result[i][0]);
    fprintf(fpResult, "%dx%d %d %d\n", 1 << i, 1 << i, result[i][1], result[i][0]);
    free(result[i]);
  }

  // free memory
  for (int i = 0; i < matrixSize; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
  free(result);
  fclose(fp);

  return 0;
}