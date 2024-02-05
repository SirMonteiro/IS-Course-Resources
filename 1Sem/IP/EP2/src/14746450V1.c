/*********************************************************************/
/**   ACH2001 - Introducao a Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2023                          **/
/**   Turma 02 - Prof. Marcos Lordello Chaim                        **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/**   17/07/2023                                                    **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38
#define NumeroMaxJogos NumeroMaxTimes *NumeroMaxRodadas

typedef struct auxtime
{
  int PontosGanhos;
  int GolsMarcados;
  int GolsSofridos;
  int SaldoDeGols;
  int Vitorias;
  int Empates;
  int Derrotas;
  float GolAverage;
  char nome[31];
} time;

typedef struct auxjogo
{
  char local[30];
  char visitante[30];
  int golslocal;
  int golsvisitante;
} jogo;

void lenometime(char *s)
{
  int i;
  s[0] = '\0';
  char c;
  c = getchar();
  if (c == '\n' || c == ' ')
    c = getchar();
  for (i = 0; c != ',' && i < 30; ++i)
  {
    s[i] = c;
    c = getchar();
  }
  s[i] = '\0';
}

// Encontra se o time já está no arranjo de times do campeonato
int encontratime(time *timescampeonato, char *nome, int notimes)
{
  // retorna a posição do arranjo times de campeonato
  for (int i = 0; i < notimes; i++)
  {
    if (strcasecmp(nome, timescampeonato[i].nome) == 0)
    {
      return i;
    }
  }
  return -1;
}

// Cria a lista de times do campeonato a partir dos nojogos
int crialistatimes(time *timescampeonato, jogo *dadosjogos, int numerojogos)
{
  // preenche o arranjo timescampeonato com os times
  int notimes = 0;
  for (int i = 0; i < numerojogos; i++)
  {
    if (encontratime(timescampeonato, dadosjogos[i].local, notimes + 1) == -1)
    {
      strncpy(timescampeonato[notimes].nome, dadosjogos[i].local, 30);
      timescampeonato[notimes].GolsMarcados = 0;
      timescampeonato[notimes].GolsSofridos = 0;
      timescampeonato[notimes].Vitorias = 0;
      timescampeonato[notimes].Empates = 0;
      timescampeonato[notimes].Derrotas = 0;
      timescampeonato[notimes].PontosGanhos = 0;
      timescampeonato[notimes].SaldoDeGols = 0;
      timescampeonato[notimes].GolAverage = 0;
      notimes++;
    }

    if (encontratime(timescampeonato, dadosjogos[i].visitante, notimes + 1) == -1)
    {
      strncpy(timescampeonato[notimes].nome, dadosjogos[i].visitante, 30);
      timescampeonato[notimes].GolsMarcados = 0;
      timescampeonato[notimes].GolsSofridos = 0;
      timescampeonato[notimes].Vitorias = 0;
      timescampeonato[notimes].Empates = 0;
      timescampeonato[notimes].Derrotas = 0;
      timescampeonato[notimes].PontosGanhos = 0;
      timescampeonato[notimes].SaldoDeGols = 0;
      timescampeonato[notimes].GolAverage = 0;
      notimes++;
    }
  }
  return notimes; // retorna o número de times. O zero é só para compilar
}

// Return gol average
float GolAverage(int golsMarcados, int golsSofridos)
{
  if (golsSofridos == 0)
    return golsMarcados;
  return (float)golsMarcados / golsSofridos;
}

// Computa dados times
void computadadostimes(time *timescampeonato, int notimes, jogo *dadosjogos, int numerojogos)
{
  // Preenche os campos do arranjo timescampeonato: Vitorias,
  // GolsSofridos, GolsMarcados, Golsaverage, SaldoDeGols, PontosGanhos.

  for (int i = 0; i < numerojogos; i++)
  {
    int indexLocal = encontratime(timescampeonato, dadosjogos[i].local, notimes);
    int indexVisitante = encontratime(timescampeonato, dadosjogos[i].visitante, notimes);
    timescampeonato[indexLocal].GolsMarcados += dadosjogos[i].golslocal;
    timescampeonato[indexLocal].GolsSofridos += dadosjogos[i].golsvisitante;
    timescampeonato[indexVisitante].GolsMarcados += dadosjogos[i].golsvisitante;
    timescampeonato[indexVisitante].GolsSofridos += dadosjogos[i].golslocal;
    if (dadosjogos[i].golslocal > dadosjogos[i].golsvisitante)
    {
      timescampeonato[indexLocal].Vitorias++;
      timescampeonato[indexVisitante].Derrotas++;
      timescampeonato[indexLocal].PontosGanhos += 3;
    }
    else if (dadosjogos[i].golslocal < dadosjogos[i].golsvisitante)
    {
      timescampeonato[indexVisitante].Vitorias++;
      timescampeonato[indexLocal].Derrotas++;
      timescampeonato[indexVisitante].PontosGanhos += 3;
    }
    else
    {
      timescampeonato[indexLocal].Empates++;
      timescampeonato[indexVisitante].Empates++;
      timescampeonato[indexLocal].PontosGanhos++;
      timescampeonato[indexVisitante].PontosGanhos++;
    }
  }

  for (int i = 0; i < notimes; i++)
  {
    timescampeonato[i].SaldoDeGols = timescampeonato[i].GolsMarcados - timescampeonato[i].GolsSofridos;
    timescampeonato[i].GolAverage = GolAverage(timescampeonato[i].GolsMarcados, timescampeonato[i].GolsSofridos);
  }

  // printf("P\tV\tGP\tGC\tSG\tGA\tNome\n");
  // for (int i = 0; i < notimes; i++)
  // {

  //   time time = timescampeonato[i];
  //   printf("%i\t%i\t%i\t%i\t%i\t%i\t%s\n", time.PontosGanhos, time.Vitorias, time.GolsMarcados, time.GolsSofridos, time.SaldoDeGols, time.GolAverage, time.nome);
  // }
}

// teams inserction sort
void insertionSortTime(time *timescampeonato, int notimes, int property)
{
  int keySort, j;
  time key;
  for (int i = 1; i < notimes; i++)
  {
    keySort = timescampeonato[i].PontosGanhos;
    key = timescampeonato[i];
    for (j = i - 1; j >= 0 && timescampeonato[j].PontosGanhos < keySort; j--)
    {
      timescampeonato[j + 1] = timescampeonato[j];
    }
    timescampeonato[j + 1] = key;
  }
}

int *findRepeatedElement(int array[], int n, int index)
{
  int *repeated = malloc(sizeof(int));
  int repeatedSize = 0;
  for (int i = index + 1; i < n; i++)
  {
    if (array[i] == array[index])
    {
      repeatedSize++;
      repeated = realloc(repeated, sizeof(int) * (repeatedSize + 1));
      repeated[repeatedSize] = i;
    }
    else
      break;
  }
  if (repeatedSize > 0)
  {
    repeated[0] = repeatedSize;
    return repeated;
  }
  else
  {
    repeated[0] = -1;
    return repeated;
  }
}

// Imprime classificação

void imprimeclassificacao(time *timescampeonato, int notimes)
{
  insertionSortTime(timescampeonato, notimes, 0);
  int points[notimes];
  for (int i = 0; i < notimes; i++)
  {
    points[i] = timescampeonato[i].PontosGanhos;
  }

  int pointsLength = sizeof(points) / sizeof(points[0]);
  int repeatedLength, keySort, repeatedElement;
  time key;
  for (int i = 0; i < notimes; i++)
  {
    int *repeatedElementFunc = findRepeatedElement(points, pointsLength, i);
    repeatedLength = repeatedElementFunc[0];
    for (int j = 1; j < repeatedLength + 1; j++)
    {
      repeatedElement = findRepeatedElement(points, pointsLength, i)[j];
      key = timescampeonato[repeatedElement];
      keySort = timescampeonato[repeatedElement].SaldoDeGols;
      if (timescampeonato[i].SaldoDeGols < keySort)
      {
        timescampeonato[repeatedElement] = timescampeonato[i];
        timescampeonato[i] = key;
      }
    }
    free(repeatedElementFunc);
  }

  printf("Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average\n");
  for (int i = 0; i < notimes; i++)
  {
    printf("%i,%s,%i,%i,%i,%i,%i,%.3f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos, timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
    // printf("%i,%i\n", timescampeonato[i].GolsMarcados, timescampeonato[i].GolsSofridos);
    // printf("%f\n", ((float)timescampeonato[i].GolsMarcados / timescampeonato[i].GolsSofridos));
  }
}

time *informacoesTime(time *timescampeonato, int notimes, char *nome)
{
  for (int i = 0; i < notimes; i++)
    if (strcasecmp(nome, timescampeonato[i].nome) == 0)
      return &timescampeonato[i];
  return NULL;
}

// Salva os dados da classificação dos tipos em arquivo no disco
void salvaclassificacao(time *timescampeonato, int notimes, char *arquivo)
{
  FILE *fp = fopen(arquivo, "w");
  if (fp == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    exit(1);
  }
  for (int i = 0; i < notimes; i++)
  {
    fprintf(fp, "%s,%i,%i,%i,%i,%i,%f\n", timescampeonato[i].nome, timescampeonato[i].PontosGanhos, timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
  }
  fclose(fp);
}

int main()
{
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxJogos];
  int i, nojogos, golslocal = 0, golsvisitante = 0;
  char local[30], visitante[30];

  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for (i = 0; i <= NumeroMaxJogos; ++i)
  {
    lenometime(local);
    lenometime(visitante);
    scanf("%d,%d", &golslocal, &golsvisitante);

    if (golslocal < 0 || golsvisitante < 0)
      break; // termina a entrada de dados

    strncpy(jogos[i].local, local, 30);
    strncpy(jogos[i].visitante, visitante, 30);

    jogos[i].golslocal = golslocal;
    jogos[i].golsvisitante = golsvisitante;
  }
  nojogos = i;

  // Confirmando os valores lidos
  // for (i = 0; i < nojogos; ++i)
  //   printf("%s,%s,%d,%d\n", jogos[i].local, jogos[i].visitante, jogos[i].golslocal, jogos[i].golsvisitante);
  // printf("\n");

  int notimes = crialistatimes(times, jogos, nojogos);
  // printf("Numero de times = %d\n", notimes);

  computadadostimes(times, notimes, jogos, nojogos);

  imprimeclassificacao(times, notimes);

  // printf("Vitórias do Corinthians no campeonato: %i\n", informacoesTime(times, notimes, "Corinthians")->Vitorias);

  // Opcional
  salvaclassificacao(times, notimes, "campeonatoIP.dat");
}
