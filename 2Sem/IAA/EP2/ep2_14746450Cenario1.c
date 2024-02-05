/*********************************************************************/
/**   ACH2002 - Introducao a Analise de Algoritmos                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 01 - Prof.Dra. Ariane Machado Lima                      **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/**   20/12/2023                                                    **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_FINENAME 256 // tamanho máximo do nome do arquivo
#define MAX_UPDATES 200  // tamanho máximo de atualizações

typedef struct
{
  int length, index;
} UPDATE;

typedef struct
{
  char action;
  int when, update, length;
} NEWUPDATE;

NEWUPDATE nextNewUpdate(FILE *file)
{
  NEWUPDATE new;
  fscanf(file, "\n%c %d %d %d", &new.action, &new.when, &new.update, &new.length);
  return new;
}

// função que recebe o vetor de atualizações junto com seu tamanho e exibe
void printUpdates(int arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}

void sort(int arr[], int arr2[], int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = arr[i];
    int i2 = arr2[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      arr2[j + 1] = arr2[j];
      j = j - 1;
    }
    arr[j + 1] = key;
    arr2[j + 1] = i2;
  }
}

void sort2(UPDATE *update, int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = update[i].length;
    UPDATE keyUpdate = update[i];
    // int i2 = arr2[i];
    j = i - 1;

    while (j >= 0 && update[j].length > key)
    {
      // arr[j + 1] = arr[j];
      update[j + 1] = update[j];
      j = j - 1;
    }
    // arr[j + 1] = key;
    update[j + 1] = keyUpdate;
  }
}

// função do cenário 1 estático que recebe a quantidade de horas, o arquivo e o
// vetor e calcula o máximo e quais atualizações
void cenario1(int horas, FILE *file, int updatesLength, int *result)
{
  // lê as atualizações do arquivo
  int updates[updatesLength];
  int updatesIndex[updatesLength];
  UPDATE updatesStruct[updatesLength];
  for (int i = 0; i < updatesLength; i++)
  {
    fscanf(file, "%d", &updates[i]);
    updatesStruct[i].index = i;
    updatesStruct[i].length = updates[i];
    updatesIndex[i] = i + 1;
  }

  // ordena as atualizações baseado nas atualizações que terminam primeiro
  sort(updates, updatesIndex, updatesLength);

  // calcula o máximo de atualizações
  int sum = horas;
  int counter = 0;
  for (int i = 0; i < updatesLength; i++)
  {
    if (sum - updates[i] >= 0)
    {
      counter++;
      sum -= updates[i];
    }
    else
      break;
  }

  // armazena na variável result a quantidade e quais atualizações foram feitas
  result[0] = counter;
  for (int i = 1; i < counter + 1; i++)
  {
    result[i] = updatesIndex[i - 1];
  }

  // exiba a duração das atualizações
  printf("Duração das atualizações: ");
  for (int i = 0; i < updatesLength; i++)
  {
    printf("%d ", updates[i]);
  }
  printf("\n");

  // exiba o index
  printf("Index das atualizações:   ");
  for (int i = 0; i < updatesLength; i++)
  {
    printf("%d ", updatesIndex[i]);
  }
  printf("\n");

  // exibe as horas restantes pós atualizações
  printf("horas restantes: %d\n", sum);

  return;
}

void minHeapify(int arr[], int n, int i)
{
  int min;
  int left = 2 * i;
  int right = 2 * i + 1;
  if (left <= n && arr[left] < arr[right])
    min = left;
  else
    min = i;
  if (right <= n && arr[right] < arr[min])
    min = right;
  if (min != i)
  {
    int aux = arr[i];
    arr[i] = arr[min];
    arr[min] = aux;
    minHeapify(arr, n, min);
  }
}

void buildMinHeap(int arr[], int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    minHeapify(arr, n, i);
}

int minHeapExtract(int arr[], int *n)
{
  if (*n < 1)
    return -1;
  int node = arr[0];
  arr[0] = arr[*n - 1];
  *n = *n - 1;
  minHeapify(arr, *n, 0);
  return node;
}

int minHeapMinimum(int arr[], int *n)
{
  if (*n < 1)
    return -1;
  return arr[0];
}

void minHeapDecreaseKey(int arr[], int i, int key)
{
  if (key > arr[i])
  {
    printf("Erro: chave é maior que a chave atual\n");
    return;
  }
  arr[i] = key;
  while (i > 0 && arr[(i - 1) / 2] > arr[i])
  {
    int temp = arr[i];
    arr[i] = arr[(i - 1) / 2];
    arr[(i - 1) / 2] = temp;
    i = (i - 1) / 2;
  }
}

void minHeapInsert(int arr[], int *n, int key)
{
  *n = *n + 1;
  arr[*n - 1] = INT_MAX;
  minHeapDecreaseKey(arr, *n - 1, key);
}

void cenario2(int horas, FILE *file, int updatesLength, int *result)
{
  // lê as atualizações do arquivo
  int updates[updatesLength];
  int updatesIndex[updatesLength];
  UPDATE *updatesStruct = (UPDATE *)malloc(sizeof(UPDATE) * updatesLength);
  for (int i = 0; i < updatesLength; i++)
  {
    fscanf(file, "%d", &updates[i]);
    updatesStruct[i].index = i;
    updatesStruct[i].length = updates[i];
    updatesIndex[i] = i + 1;
  }

  NEWUPDATE newUpdate = nextNewUpdate(file);

  buildMinHeap(updates, updatesLength);

  printUpdates(updates, updatesLength);

  // calcula o máximo de atualizações
  // int sum = horas;
  // int counter = 0;
  // for (int i = 0; i < updatesLength; i++)
  // {
  //   if (newUpdate.when == i)
  //   {
  //     if (newUpdate.action == 'i')
  //     {
  //       minHeapInsert(updates, &updatesLength, newUpdate.length);
  //     }
  //     else
  //     {
  //       minHeapDecreaseKey(updates, newUpdate.update, newUpdate.length);
  //     }
  //     newUpdate = nextNewUpdate(file);
  //   }
  //   if (sum - minHeapExtract(updates, &updatesLength) >= 0)
  //   {
  //     counter++;
  //     sum -= updates[i];
  //   }
  //   else
  //     break;
  // }

  int hoursPassed = 0;
  int counter = 0;
  while (horas - hoursPassed >= minHeapMinimum(updates, &updatesLength))
  {
    hoursPassed += minHeapExtract(updates, &updatesLength);
    counter++;
    if (newUpdate.when <= hoursPassed)
    {
      if (newUpdate.action == 'i')
      {
        minHeapInsert(updates, &updatesLength, newUpdate.length);
      }
      else
      {
        minHeapDecreaseKey(updates, newUpdate.update, newUpdate.length);
      }
      newUpdate = nextNewUpdate(file);
    }
    // if (!(minHeapMinimum(updates, updatesLength) <= horas - hoursPassed))
    //   break;
  }

  printUpdates(updates, updatesLength);

  // insertToMinHeap(updates, &updatesLength, 4);
  // increaseKeyToMinHeap(updates, 0, 100);
  // printf("\n[%d]\n", extractMinNodeFromHeap(updates, &updatesLength));

  // MinHeapInsert(updates, &updatesLength, 100);
  // minHeapDecreaseKey(updates, 1, 1);

  // printf("\n");
  // for (int i = 0; i < updatesLength; i++)
  // {
  //   printf("%d, ", updates[i]);
  // }
  // printf("\n");

  // armazena na variável result a quantidade e quais atualizações foram feitas
  result[0] = counter;

  return;
}

// função que recebe o vetor result e exibe o resultado
void printResult(int *result)
{
  for (int i = 0; i < result[0] + 1; i++)
  {
    printf("%d ", result[i]);
  }
  printf("\n");
}

// função que recebe o vetor result e o cenario e escreve o resultado no arquivo
void writeFile(int *result, int cenario)
{
  char filename[MAX_FINENAME];
  sprintf(filename, "saida%d.txt", cenario);
  FILE *file = fopen(filename, "w");
  // for (int i = 0; i < result[0] + 1; i++)
  // {
  //   fprintf(file, "%d ", result[i]);
  // }
  int i = 0;
  while (i < result[0] + 1)
  {
    fprintf(file, "%d", result[i]);
    i++;
    if (i < result[0] + 1)
      fprintf(file, " ");
  }
  fprintf(file, "\n");
  fclose(file);
}

int main(int argc, char *argv[])
{
  // verifica a quantidade de argumentos, se for diferente de 4, encerra o
  // programa
  if (argc != 4)
  {
    printf("Uso: %s <janela_de_horas> <cenário> <arquivo_de_entrada>\n",
           argv[0]);
    exit(1);
  }

  // verifica o argumento de janela de horas, se for inválido, encerra o
  // programa
  int janelaHoras = atoi(argv[1]);
  if (janelaHoras < 14 || janelaHoras > 20)
  {
    printf("O argumento <janela_de_horas> deve ser um número inteiro entre 1 e "
           "14\n");
    exit(1);
  }

  // verifica o argumento de cenário, se for inválido, encerra o programa
  int cenario = atoi(argv[2]);
  if (cenario != 1 && cenario != 2)
  {
    printf("O argumento <cenário> deve ser um número inteiro sendo 1 ou 2\n");
    exit(1);
  }

  // copia o nome do arquivo e lê o arquivo, se não for possível, encerra o
  // programa
  char filename[MAX_FINENAME];
  strcpy(filename, argv[3]);
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Não foi possível abrir o arquivo %s\n", filename);
    exit(1);
  }

  // lê a quantidade de atualizações do primeiro dígito do arquivo e verifica se
  // é válido
  int updatesLength;
  fscanf(file, "%d", &updatesLength);
  if (updatesLength > MAX_UPDATES)
  {
    printf("O arquivo de entrada deve conter no máximo %d atualizações\n",
           MAX_UPDATES);
    exit(1);
  }

  // declara result
  int result[MAX_UPDATES];

  // executa o cenário 1 ou 2 e armazena na variável result
  if (cenario == 1)
    cenario1(janelaHoras, file, updatesLength, result);
  else
    cenario2(janelaHoras, file, updatesLength, result);

  // escreve o resultado no arquivo de saída
  writeFile(result, cenario);

  // exibe result
  printResult(result);

  return 0;
}
