// sum a number by reference

#include <stdio.h>

void sum(int *x)
{
    *x = *x + 1;
}

int main()
{
    int x = 0;
    sum(&x);
    printf("%i\n", x);
    return 0;
}