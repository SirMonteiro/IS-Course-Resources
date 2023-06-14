/*********************************************************************/
/**   ACH2001 - Introducao a Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2023                          **/
/**   Turma 02 - Prof. Marcos Lordello Chaim                        **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adicione funções auxiliares se for necessário

// GCD (greatest commom divisor) using Euclidean algorithm
int gcd(int x, int y)
{
  while (y > 0)
  {
    int holdY = y;
    y = x % y;
    x = holdY;
  }
  return x;
}

// LCM (least commom multiple) using GCD
int lcm(int x, int y)
{
  return x * y / gcd(x, y);
}

// LCM with array
int calculateLCM(int array[], int n)
{
  int result = 1;

  for (int i = 0; i < n; i++)
  {
    result = lcm(result, array[i]);
  }

  return result;
}

bool isLeapYear(int year)
{
  if ((!(year % 4) && year % 100) || !(year % 400))
    return true;
  else
    return false;
}

bool verificaDataValida(int d, int m, int a)
{
  // Adicione seu código
  if (a < 0 || m < 1 || m > 12)
  {
    return false;
  }

  int maxDays;

  switch (d)
  {
  case 2:
    // isLeapYear(a) ? maxDays = 29; : maxDays = 28;
    if (isLeapYear(a))
      maxDays = 29;
    else
      maxDays = 28;
    break;
  case 4:
  case 6:
  case 9:
  case 10:
    maxDays = 30;
    break;
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 11:
  case 12:
    maxDays = 31;
    break;
  default:
    return false;
  }

  if (d > maxDays)
    return false;
  return true;
}

int countDays(int day, int month, int year)
{
  int sum = 0;
  int monthMaxDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 30, 31, 31};
  if (isLeapYear(year))
    monthMaxDays[1] = 29;
  for (int i = 0; i < (month - 1); i++)
  {
    sum += monthMaxDays[i];
  }
  return sum + day;
}

void countToDay(int count, int year)
{
  int monthMaxDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 30, 31, 31};
  if (isLeapYear(year))
    monthMaxDays[1] = 29;

  int i;
  for (i = 0; i < 12; i++)
  {
    if (count <= monthMaxDays[i])
      break;
    count -= monthMaxDays[i];
  }
  printf("%i/%i", count, i + 1);
}

int main()
{
  int dia, mes, ano;

  printf("Entre com a data de inicio do ano letivo:\n");
  printf("Entre com o dia: ");
  scanf("%d", &dia);
  printf("Entre com o mes: ");
  scanf("%d", &mes);
  printf("Entre com o ano: ");
  scanf("%d", &ano);

  if (!verificaDataValida(dia, mes, ano))
  {
    printf("Dados incorretos\n");
    exit(1); // Esta função aborta a execução do programa.
  }

  // Adicione seu código

  int periodoAulas[] = {2, 3, 4, 5, 6};
  int LCM = calculateLCM(periodoAulas, 5);
  int days = countDays(dia, mes, ano);
  printf("Proximos dias de encontro de todos os clubes:\n");
  while (days < (isLeapYear(ano) ? 366 : 365) - LCM)
  {
    days = days + LCM;
    countToDay(days, ano);
    printf("/%i\n", ano);
  }

  return 0;
}
