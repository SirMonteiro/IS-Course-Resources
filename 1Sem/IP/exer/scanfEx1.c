#include <stdio.h>

int main()
{
  float celsius;
  printf("%s", "Insira a temperatura em celsius para transformar em Fahrenheit: ");
  scanf("%f", &celsius);
  printf("%s %f %s", "A temperatura é: ", 1.8 * celsius + 32, "ºF\n");
  printf("A temperatura é:  %f ºF\n", 1.8 * celsius + 32);
  return 0;
}