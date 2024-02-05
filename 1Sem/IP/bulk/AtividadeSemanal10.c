#include <stdio.h>
#include <stdlib.h>

int contaCaracteres(char** palavras, int n){
  int total = 0;

  /* COMPLETE */
  
  return total;
}

  
int main() {
  char** nomes2 = (char**) malloc(sizeof(char*)*4);
  nomes2[0] = (char*) malloc(sizeof(char)*10);
  nomes2[1] = (char*) malloc(sizeof(char)*6);
  nomes2[2] = (char*) malloc(sizeof(char)*6);
  nomes2[3] = (char*) malloc(sizeof(char)*9);
  
  nomes2[0][0] = 'A';
  nomes2[0][1] = 'l';
  nomes2[0][2] = 'v';
  nomes2[0][3] = 'e';
  nomes2[0][4] = 'n';
  nomes2[0][5] = 'a';
  nomes2[0][6] = 'r';
  nomes2[0][7] = 'i';
  nomes2[0][8] = 'a';
  nomes2[0][9] = '\0';
  nomes2[1][0] = 'V';
  nomes2[1][1] = 'i';
  nomes2[1][2] = 'n';
  nomes2[1][3] = 'i';
  nomes2[1][4] = 'l';
  nomes2[1][5] = '\0';
  nomes2[2][0] = 'F';
  nomes2[2][1] = 'i';
  nomes2[2][2] = 'b';
  nomes2[2][3] = 'r';
  nomes2[2][4] = 'a';
  nomes2[2][5] = '\0';
  nomes2[3][0] = 'P';
  nomes2[3][1] = 'l';
  nomes2[3][2] = 'a';
  nomes2[3][3] = 's';
  nomes2[3][4] = 't';
  nomes2[3][5] = 'i';
  nomes2[3][6] = 'c';
  nomes2[3][7] = 'o';
  nomes2[3][8] = '\0';

  printf("Total de caracteres: %i\n", contaCaracteres(nomes2,4));
  
  return 0;
}


/* SAIDA
Total de caracteres: 27
*/