/*********************************************************************/
/**   ACH2001 - Introducao a Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2023                          **/
/**   Turma 02 - Prof. Marcos Lordello Chaim                        **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/**   12/07/2023                                                    **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38

typedef struct auxtime
{
  int PontosGanhos;
  int GolsMarcados;
  int GolsSofridos;
  int SaldoDeGols;
  int Vitorias;
  int GolAverage;
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
  for (i = 0; c != ',' && i < 30; ++i)
  {
    s[i] = c;
    c = getchar();
  }
  if (s[0] == '\n' || s[0] == ' ')
  {
    s[0] = '\2';
  }
  s[i] = '\0';
  // printf("%s\n", s);
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
      timescampeonato[notimes].PontosGanhos = 0;
      timescampeonato[notimes].SaldoDeGols = 0;
      timescampeonato[notimes].GolAverage = 0;
      notimes++;
    }
  }

  return notimes; // retorna o número de times. O zero é só para compilar
}

// Computa dados times

int GolAverage(int golsMarcados, int golsSofridos)
{
  if (golsSofridos == 0)
    return golsMarcados;
  return golsMarcados / golsSofridos;
}

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
      timescampeonato[indexLocal].PontosGanhos += 3;
    }
    else if (dadosjogos[i].golslocal < dadosjogos[i].golsvisitante)
    {
      timescampeonato[indexVisitante].Vitorias++;
      timescampeonato[indexVisitante].PontosGanhos += 3;
    }
    else
    {
      timescampeonato[indexLocal].PontosGanhos++;
      timescampeonato[indexVisitante].PontosGanhos++;
    }
  }

  for (int i = 0; i < notimes; i++)
  {
    timescampeonato[i].SaldoDeGols = timescampeonato[i].GolsMarcados - timescampeonato[i].GolsSofridos;
    timescampeonato[i].GolAverage = GolAverage(timescampeonato[i].GolsMarcados, timescampeonato[i].GolsSofridos);
  }

  for (int i = 0; i < notimes; i++)
  {
    printf("computadadostimes: nome = %s\n", timescampeonato[i].nome);
    printf("computadadostimes: GolsMarcados = %d\n", timescampeonato[i].GolsMarcados);
    printf("computadadostimes: GolsSofridos = %d\n", timescampeonato[i].GolsSofridos);
    printf("computadadostimes: Vitorias = %d\n", timescampeonato[i].Vitorias);
    printf("computadadostimes: PontosGanhos = %d\n", timescampeonato[i].PontosGanhos);
    printf("computadadostimes: SaldoDeGols = %d\n", timescampeonato[i].SaldoDeGols);
    printf("computadadostimes: GolAverage = %d\n", timescampeonato[i].GolAverage);
  }
}

// Insertion Sort
int insertionSort(float array[], int n)
{
  int key, j;
  for (int i = 1; i < n; i++)
  {
    key = array[i];
    j = i - 1;
    while (j >= 0 && array[j] < key)
    {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = key;
  }
}

// teams inserction sort
int insertionSortTime(time *timescampeonato, int notimes, int property)
{
  int keySort, j, timeJ;
  time key;
  for (int i = 1; i < notimes; i++)
  {
    if (property == 0)
    {
      keySort = timescampeonato[i].PontosGanhos;
      timeJ = timescampeonato[j].PontosGanhos;
    }
    else if (property == 1)
    {
      keySort = timescampeonato[i].SaldoDeGols;
      timeJ = timescampeonato[j].SaldoDeGols;
    }
    key = timescampeonato[i];
    j = i - 1;
    while (j >= 0 && timeJ < keySort)
    {
      timescampeonato[j + 1] = timescampeonato[j];
      j--;
    }
    timescampeonato[j + 1] = key;
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

  // int n = sizeof(points) / sizeof(points[0]);
  // insertionSort(points, n);

  for (int i = 0; i < notimes; i++)
  {
    printf("imprimeclassificacao: points[%d] = %d\n", i, points[i]);
  }
}

// Salva os dados da classificação dos tipos em arquivo no disco

void salvaclassificacao(time *timescampeonato, int notimes, char *arquivo)
{
}

int main()
{
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxRodadas];
  int i, nojogos, golslocal = 0, golsvisitante = 0;
  char local[30], visitante[30];

  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for (i = 0; i <= NumeroMaxRodadas; ++i)
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
  for (i = 0; i < nojogos; ++i)
    printf("%s,%s,%d,%d\n", jogos[i].local, jogos[i].visitante, jogos[i].golslocal, jogos[i].golsvisitante);
  printf("\n");

  int notimes = crialistatimes(times, jogos, nojogos);
  printf("Numero de times = %d\n", notimes);

  computadadostimes(times, notimes, jogos, nojogos);

  imprimeclassificacao(times, notimes);

  // Opcional
  salvaclassificacao(times, notimes, "campeonatoIP.dat");
}
