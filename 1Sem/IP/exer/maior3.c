#include <stdio.h>

char *aliquot(float salary)
{
  if (salary < 1903.99)
  {
    return "Isento";
  }
  else if (salary < 2826.66)
  {
    return "7,5\%";
  }
  else if (salary < 3751.06)
  {
    return "15\%";
  }
  else if (salary < 4664.68)
  {
    return "22,5\%";
  }
  return "27,5%";
}

int main()
{
  float salary;

  printf("Entre com o salário: ");

  scanf("%f", &salary);

  // Inclua seu código.
  printf("%s\n", aliquot(salary));

  return 0;
}
