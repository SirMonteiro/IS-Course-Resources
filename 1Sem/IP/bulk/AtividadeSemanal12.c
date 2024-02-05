#include <stdio.h>
#include <stdlib.h>

int palindromo(char* texto, int n) {

  /* COMPLETAR */

  return 1;
}

int main() {
  char* p1 = (char*) malloc(sizeof(char)*5);
  p1[0] = 'r';
  p1[1] = 'a';
  p1[2] = 'd';
  p1[3] = 'a';
  p1[4] = 'r';

  if(palindromo(p1,5)){
    printf("radar eh palindromo!\n");
  }else{
    printf("radar nao eh palindromo!\n");
  }

  if(palindromo(p1,4)){
    printf("rada eh palindromo!\n");
  }else{
    printf("rada nao eh palindromo!\n");
  }

  
  return 0;
}


/* SAIDA
radar eh palindromo!
rada nao eh palindromo!
*/