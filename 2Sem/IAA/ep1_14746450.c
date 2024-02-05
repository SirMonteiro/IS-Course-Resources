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
int **findMax(int exponent, int **matrix, int *matrixSize, int **result)
{
  if (exponent == 0)
  {
    if (matrix[0][0])
      result[0][1]++;
    else
      result[0][0]++;
    free(matrix[0]);
    free(matrix);
    return NULL;
  }
  if (exponent == 1)
  {
    int **matrixAux = (int **)malloc(sizeof(int *) * (*matrixSize) / 2);
    for (int i = 0; i < (*matrixSize) / 2; i++)
    {
      matrixAux[i] = (int *)malloc(sizeof(int) * (*matrixSize) / 2);
    }

    int auxBlack, auxWhite;
    for (int i = 0; i < (*matrixSize); i = i + 2)
    {
      for (int j = 0; j < (*matrixSize); j = j + 2)
      {
        auxBlack = result[exponent - 1][0];
        auxWhite = result[exponent - 1][1];
        matrix[i][j] == 0 ? result[exponent - 1][0]++ : result[exponent - 1][1]++;
        matrix[i][j + 1] == 0 ? result[exponent - 1][0]++ : result[exponent - 1][1]++;
        matrix[i + 1][j] == 0 ? result[exponent - 1][0]++ : result[exponent - 1][1]++;
        matrix[i + 1][j + 1] == 0 ? result[exponent - 1][0]++ : result[exponent - 1][1]++;
        if (result[exponent - 1][0] - auxBlack == 4)
        {
          result[exponent][0]++;
          result[exponent - 1][0] -= 4;
          matrixAux[i / 2][j / 2] = 0;
        }
        else if (result[exponent - 1][1] - auxWhite == 4)
        {
          result[exponent][1]++;
          result[exponent - 1][1] -= 4;
          matrixAux[i / 2][j / 2] = 1;
        }
        else
        {
          matrixAux[i / 2][j / 2] = -1;
        }
      }
      free(matrix[i]);
      free(matrix[i + 1]);
    }

    // print whole matrixAux
    // for (int i = 0; i < (*matrixSize) / 2; i++)
    // {
    //   for (int j = 0; j < (*matrixSize) / 2; j++)
    //   {
    //     printf("%d\t", matrixAux[i][j]);
    //   }
    //   printf("\n");
    // }

    free(matrix);

    *matrixSize = *matrixSize / 2;
    return matrixAux;
  }
  matrix = findMax(exponent - 1, matrix, matrixSize, result);

  int **matrixAux = (int **)malloc(sizeof(int *) * (*matrixSize) / 2);
  for (int i = 0; i < (*matrixSize) / 2; i++)
  {
    matrixAux[i] = (int *)malloc(sizeof(int) * (*matrixSize) / 2);
  }

  int auxBlack, auxWhite;
  for (int i = 0; i < (*matrixSize); i = i + 2)
  {
    for (int j = 0; j < (*matrixSize); j = j + 2)
    {
      auxBlack = result[exponent - 1][0];
      auxWhite = result[exponent - 1][1];
      if (matrix[i][j] == 0)
        auxBlack++;
      else if (matrix[i][j] == 1)
        auxWhite++;
      if (matrix[i][j + 1] == 0)
        auxBlack++;
      else if (matrix[i][j + 1] == 1)
        auxWhite++;
      if (matrix[i + 1][j] == 0)
        auxBlack++;
      else if (matrix[i + 1][j] == 1)
        auxWhite++;
      if (matrix[i + 1][j + 1] == 0)
        auxBlack++;
      else if (matrix[i + 1][j + 1] == 1)
        auxWhite++;

      if (auxBlack - result[exponent - 1][0] == 4)
      {
        result[exponent][0]++;
        result[exponent - 1][0] -= 4;
        matrixAux[i / 2][j / 2] = 0;
      }
      else if (auxWhite - result[exponent - 1][1] == 4)
      {
        result[exponent][1]++;
        result[exponent - 1][1] -= 4;
        matrixAux[i / 2][j / 2] = 1;
      }
      else
      {
        matrixAux[i / 2][j / 2] = -1;
      }
    }
    free(matrix[i]);
    free(matrix[i + 1]);
  }

  // print whole matrixAux
  // for (int i = 0; i < *matrixSize / 2; i++)
  // {
  //   for (int j = 0; j < *matrixSize / 2; j++)
  //   {
  //     printf("%d\t", matrixAux[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n");

  free(matrix);

  *matrixSize = *matrixSize / 2;

  if (*matrixSize == 1)
  {
    free(matrixAux[0]);
    free(matrixAux);
    return NULL;
  }
  return matrixAux;
}

int main(int argc, char *argv[])
{
  // check if the number of arguments is correct
  if (argc != 3)
  {
    printf("Este programa exige dois argumentos: <número exponent de 2: 0 a 10> e <arquivo .txt>\n");
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

  // call recursive function
  findMax(exponent, matrix, &matrixSize, result);

  // print result
  for (int i = exponent; i >= 0; i--)
  {
    printf("%dx%d %d %d\n", 1 << i, 1 << i, result[i][1], result[i][0]);
    free(result[i]);
  }

  // free memory
  free(result);
  fclose(fp);

  return 0;
}