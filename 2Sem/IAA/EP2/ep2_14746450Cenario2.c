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

// struct de um update, armazenando a duração e o número da atualização
typedef struct
{
  int length, index;
} UPDATE;

// struct de uma alteração na tabela de atualizações, armazenando
// a ação, o instante a ser modificado, o número e a duração da atualização
typedef struct
{
  char action;
  int when, update, length;
} NEWUPDATE;

// função que recebe o arquivo e retorna as linhas em forma do struct NEWUPDATE
NEWUPDATE nextNewUpdate(FILE *file)
{
  // instancia um novo struct
  NEWUPDATE new;
  // lê o arquivo e guarda o resultado no struct e a quantidade de leituras na variável isNotEOF
  // int isNotEOF = fscanf(file, "\n%c %d %d %d", &new.action, &new.when, &new.update, &new.length);

  // printf("teste: %d\n", isNotEOF);
  // verifica se for fim do arquivo e sinaliza atribuindo ao action dentro do struct
  // if (isNotEOF < 1)
  //   new.action = 'e';

  // lê o arquivo e guarda o resultado no struct, verificando se chegou no fim do arquivo
  while (fscanf(file, "\n%c %d %d %d", &new.action, &new.when, &new.update, &new.length) != EOF)
    return new;

  // caso for fim do arquivo sinaliza retornando a struct com a variável action
  new.action = 'e';

  return new;
}

// função que recebe o vetor de atualizações junto com seu tamanho e exibe
void printUpdates(UPDATE *update, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d, ", update[i].length);
  }
  printf("\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d, ", update[i].index);
  }
  printf("\n");
}

void sort(UPDATE *update, int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = update[i].length;
    UPDATE keyUpdate = update[i];
    j = i - 1;

    while (j >= 0 && update[j].length > key)
    {
      update[j + 1] = update[j];
      j = j - 1;
    }
    update[j + 1] = keyUpdate;
  }
}

void minHeapify(UPDATE *update, int n, int i)
{
  int min;
  int left = 2 * i;
  int right = 2 * i + 1;
  if (left < n && update[left].length < update[i].length)
    min = left;
  else
    min = i;
  if (right < n && update[right].length < update[min].length)
    min = right;
  if (min != i)
  {
    UPDATE aux = update[i];
    update[i] = update[min];
    update[min] = aux;
    minHeapify(update, n, min);
  }
}

void buildMinHeap(UPDATE *update, int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    minHeapify(update, n, i);
}

UPDATE minHeapExtract(UPDATE *update, int *n)
{
  if (*n < 1)
  {
    UPDATE error;
    error.index = -1;
    error.length = -1;
    printf("error\n");
    return error;
  }
  UPDATE node = update[0];
  update[0] = update[*n - 1];
  *n = *n - 1;
  update = (UPDATE *)realloc(update, sizeof(UPDATE) * (*n));
  minHeapify(update, *n, 0);
  return node;
}

int minHeapMinimum(UPDATE *update, int *n)
{
  if (*n < 1)
    return -1;
  return update[0].length;
}

void minHeapDecreaseKey(UPDATE *update, int i, int key)
{
  if (key > update[i].length)
  {
    printf("Erro1: chave é maior que a chave atual\n");
    return;
  }
  update[i].length = key;
  while (i > 0 && update[(i) / 2].length > update[i].length)
  {
    UPDATE temp = update[i];
    update[i] = update[(i) / 2];
    update[(i) / 2] = temp;
    i = (i) / 2;
  }
}

void minHeapDecreaseUpdateLength(UPDATE *update, int i, int key)
{
  int j = 0;
  while (update[j].index != i)
  {
    j++;
  }
  minHeapDecreaseKey(update, j, key);
}

void minHeapInsert(UPDATE *update, int *n, int key, int index)
{
  *n = *n + 1;
  update = (UPDATE *)realloc(update, sizeof(UPDATE) * (*n));
  update[*n - 1].length = INT_MAX;
  update[*n - 1].index = index;
  minHeapDecreaseKey(update, *n - 1, key);
}

// função do cenário 1 estático que recebe a quantidade de horas, o arquivo e o
// vetor e calcula o máximo e quais atualizações seram realizadas
void cenario1(int horas, FILE *file, int updatesLength, int *result)
{
  // lê as atualizações do arquivo
  UPDATE updates[updatesLength];
  for (int i = 0; i < updatesLength; i++)
  {
    fscanf(file, "%d", &updates[i].length);
    updates[i].index = i + 1;
  }

  // ordena as atualizações baseado nas atualizações que terminam primeiro
  sort(updates, updatesLength);

  // calcula o máximo de atualizações
  int sum = horas;
  int counter = 0;
  for (int i = 0; i < updatesLength; i++)
  {
    if (sum - updates[i].length >= 0)
    {
      counter++;
      sum -= updates[i].length;
    }
    else
      break;
  }

  // armazena na variável result a quantidade e quais atualizações foram feitas
  result[0] = counter;
  for (int i = 1; i < counter + 1; i++)
  {
    result[i] = updates[i - 1].index;
  }

  // exiba a duração das atualizações
  printf("Duração das atualizações: ");
  for (int i = 0; i < updatesLength; i++)
  {
    printf("%d ", updates[i].length);
  }
  printf("\n");

  // exiba o index
  printf("Index das atualizações:   ");
  for (int i = 0; i < updatesLength; i++)
  {
    printf("%d ", updates[i].index);
  }
  printf("\n");

  // exibe as horas restantes pós atualizações
  printf("horas restantes: %d\n", sum);

  return;
}

// função do cenário 2 dinâmico que recebe a quantidade de horas, o arquivo e o
// vetor e calcula o máximo e quais atualizações seram realizadas
void cenario2(int horas, FILE *file, int updatesLength, int *result)
{
  // aloca dinamicamente um vetor para os structs de atualizações
  UPDATE *updates = (UPDATE *)malloc(sizeof(UPDATE) * updatesLength);

  // lê as atualizações do arquivo
  for (int i = 0; i < updatesLength; i++)
  {
    fscanf(file, "%d", &updates[i].length);
    updates[i].index = i + 1;
  }

  // instancia e atribui a primeira modificação a ser feita na tabela
  NEWUPDATE newUpdate = nextNewUpdate(file);

  // constrói o heap mínimo no vetor de structs de atualizações
  buildMinHeap(updates, updatesLength);

  // printUpdates(updates, updatesLength);

  // inicializa um contador e a quantidade de horas passadas
  int hoursPassed = 0;
  int counter = 0;
  // enquanto houver espaço em horas para a próxima atualização mais rápida
  while (horas - hoursPassed >= minHeapMinimum(updates, &updatesLength))
  {
    // recebe a atualização mais rápida e refaz o heap mínimo
    UPDATE runningUpdate = minHeapExtract(updates, &updatesLength);

    printf("\n[%d|%d]\n", runningUpdate.length, runningUpdate.index);
    printUpdates(updates, updatesLength);

    // registra a atualização
    hoursPassed += runningUpdate.length;
    counter++;

    // guarda o número da atualização executada
    result[counter] = runningUpdate.index;

    // enquanto tiver mudanças a serem feitas e foi feita durante a última
    // atualização ou agora
    while (newUpdate.action != 'e' && newUpdate.when <= hoursPassed)
    {
      printf("Ocorreu uma mudança na tabela de atualizações!\n");

      if (newUpdate.action == 'i')
        minHeapInsert(updates, &updatesLength, newUpdate.length, newUpdate.update);
      else
        minHeapDecreaseUpdateLength(updates, newUpdate.update, newUpdate.length);

      newUpdate = nextNewUpdate(file);
    }
  }

  // armazena quantas atualizações ocorreram no período de tempo
  result[0] = counter;
  free(updates);

  return;
}

// função que recebe o vetor result e o cenario e escreve o resultado no arquivo
void writeFile(int *result, int cenario)
{
  char filename[MAX_FINENAME];
  sprintf(filename, "saida%d.txt", cenario);
  FILE *file = fopen(filename, "w");
  for (int i = 0; i < result[0] + 1; i++)
  {
    fprintf(file, "%d ", result[i]);
  }
  // int i = 0;
  // while (i < result[0] + 1)
  // {
  //   fprintf(file, "%d", result[i]);
  //   i++;
  //   if (i < result[0] + 1)
  //     fprintf(file, " ");
  // }
  fprintf(file, "\n");
  fclose(file);
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
