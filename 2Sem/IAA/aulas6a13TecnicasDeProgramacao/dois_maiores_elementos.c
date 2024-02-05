#include <stdio.h>
#include <limits.h>


/* Escreva uma função para obter o maior e o segundo maior elemento de um arranjo de valores inteiros sem usar nenhum laço 
  (isto é, utlizando recursão). Sugestão: as variáveis que receberão a resposta podem ser parâmetros dessa função.*/


/* Esta função identifica o maior e o segundo maior elemento de um arranjo v contendo n valores inteiros. 
   Estes valores serão armazenados, respectivamente, nas variáveis max e max2 */ 



void calculasOsDoisMaioresElementos(int* v,  int n, int* max, int* max2){
    if (n == 0){
        return;
    }
    else {
        if (v[n-1] > *max){
            *max2 = *max;
            *max = v[n-1];
        }
        else if (v[n-1] > *max2){
            *max2 = v[n-1];
        }
        calculasOsDoisMaioresElementos(v, n-1, max, max2);
    }


}

void main(){
    int max = INT_MIN, max2 = INT_MIN;
    int v[] = {9, 4, -80, 79};
    calculasOsDoisMaioresElementos(v, 4, &max, &max2);
    printf("Maior: %d, Segundo maior: %d\n", max, max2);

    max = INT_MIN, max2 = INT_MIN;
    int v2[] = {-80};
    calculasOsDoisMaioresElementos(v2, 1, &max, &max2);
    printf("Maior: %d, Segundo maior: %d\n", max, max2);

    max = INT_MIN, max2 = INT_MIN;
    int v3[] = {};
    calculasOsDoisMaioresElementos(v3, 0, &max, &max2);
    printf("Maior: %d, Segundo maior: %d\n", max, max2);
}
