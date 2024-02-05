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
#include <stdbool.h>

typedef struct team
{
  char nome[50];
  int golsMarcados;
  int golsSofridos;
  int vitorias;
  int empates;
  int pontosGanhos;
  int saldoDeGols;
  int golAverage;
} Time;

int golsMarcados, golsSofridos, vitorias, empates;

int GolAverage(golsMarcados, golsSofridos)
{
  if (golsSofridos == 0)
    return golsMarcados;
  return golsMarcados / golsSofridos;
}

int main()
{
  int pontosGanhos = 3 * vitorias + empates;
  int saldoDeGols = golsMarcados - golsSofridos;
  int golAverage = GolAverage(golsMarcados, golsSofridos);

  struct team Time1;

  printf("Digite o nome do time: ");
  scanf("%s", Time1.nome);

  printf("Digite o numero de gols marcados: ");
  scanf("%d", &Time1.golsMarcados);

  printf("%s", Time1.nome);

  return 0;
}
