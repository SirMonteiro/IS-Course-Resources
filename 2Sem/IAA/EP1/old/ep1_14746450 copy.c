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
  if (matrixSize == 1)
  {
    // create matrix to use with the values read from file
    // int **matrix = (int **)malloc(sizeof(int *) * totalMatrixSize);
    // for (int i = 0; i < totalMatrixSize; i++)
    // {
    //   matrix[i] = (int *)malloc(sizeof(int) * totalMatrixSize);
    // }

    // create result matrix
    // int **resultMatrix = (int **)malloc(sizeof(int *) * (expoente + 1));
    // for (int i = 0; i < (expoente + 1); i++)
    // {
    //   resultMatrix[i] = (int *)malloc(sizeof(int) * 2);
    // }

    // read values from file and put them in the matrix
    int readValue;
    for (int i = 0; i < totalMatrixSize; i++)
    {
      for (int j = 0; j < totalMatrixSize; j++)
      {
        // fscanf(fp, "%1d", &matrix[i][j]);
        fscanf(file, "%1d", &readValue);
        if (readValue == 0)
        {
          result[expoente] += 1;
        }
        else
        {
          result[expoente + 1] += 1;
        }
      }
    }

    // print result matrix
    // for (int i = 0; i < (expoente + 1); i++)
    // {
    //   printf("%d %d\n", resultMatrix[i][0], resultMatrix[i][1]);
    // }

    // print the matrix
    // for (int i = 0; i < totalMatrixSize; i++)
    // {
    //   for (int j = 0; j < totalMatrixSize; j++)
    //   {
    //     printf("%d", matrix[i][j]);
    //   }
    //   printf("\n");
    // }

    // char teste[100];
    // for (int i = 0; i < totalMatrixSize; i++)
    // {
    //   fscanf(fp, "%s", teste);
    //   printf("%s\n", teste);
    // }

    return 1;
  }
  else
  {
    // printf("matrixSize: %d\n", matrixSize); // print the current matrix size
    findMax(expoente - 1, totalMatrixSize, file, result);
    printf("passou por aqui %d\n", matrixSize);
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

  free(result);
  return 0;
}