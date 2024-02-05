/*
	Programa que cria um arranjo utilizando alocação dinâmica de memória
	com quatro elementos e imprime seus valores.
*/
#include <stdio.h>
#include <stdlib.h>

const int ALVENARIA = 0;
const int VINIL = 1;
const int FIBRA = 2;
const int PLASTICO = 3;

int main() {
   double* precos = (double*) malloc(sizeof(double)*4);
   precos[0] = 1500;
   precos[1] = 1100;
   precos[2] = 750;
   precos[3] = 500;

   int i;
   for (i=ALVENARIA; i<PLASTICO; i++){
      printf("%8.2f\n", precos[i]);
   }
   return 0;
}



/* SAIDA
 1500.00
 1100.00
  750.00
  500.00
*/