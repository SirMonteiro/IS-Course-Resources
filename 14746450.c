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
/*
esporte: 2 dias
literatura: 3 dias
fotografia: 4 dias
xadrez: 5 dias
musica: 6 dias
*/

#include <stdio.h>
#include <stdlib.h>

// Adicione funções auxiliares se for necessário
int calculaMMC(int x, int y)
{
  // Adicione seu código aqui
  int holdY;
  int multiplication = x * y;
  while (y > 0)
  {
    holdY = y;
    y = x % y;
    x = holdY;
  }
  return multiplication / x;

  return 0;
}

int verificaDataValida(int d, int m, int a)
{
  // Adicione seu código
  return 1;
  return 0;
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

  printf("%s", "teste");
  return 0;
}
