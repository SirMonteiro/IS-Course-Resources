#include <stdio.h>
#include <stdbool.h>

int ordem(int v[], int n)
{
    bool aumentou = false;
    bool diminuiu = false;
    int i;
    for (i = 0; i < n - 1; i++)
    {
        if (v[i] < v[i + 1])
            aumentou = true;
        if (v[i] > v[i + 1])
            diminuiu = true;
        if (aumentou && diminuiu)
            return 0; // sem ordem
    }
    if (aumentou)
        return 1;
    if (diminuiu)
        return -1;
    return (9); // constante
}

int main()
{
    int v[] = {1, 2, 3};
    int vN = sizeof(v) / sizeof(v[0]);
    printf("%i\n", ordem(v, vN));
    return 0;
}
