#include <stdio.h>

int main()
{
  unsigned int largura, altura;
  unsigned int counterLargura, counterAltura;

  scanf("%i %i", &largura, &altura);
  while (counterAltura < altura)
  {
    while (counterLargura < largura)
    {
      printf("%s", "#");
      counterLargura++;
    }
    printf("\n");
    counterLargura = 0;
    counterAltura++;
  }
  return 0;
}