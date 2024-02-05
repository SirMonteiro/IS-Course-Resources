#include <stdio.h>
#include <stdbool.h>

int sort(int v[], int n)
{
    int state = 9;
    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] < v[i + 1])
        {
            if (i != 0 && state != 1)
                return 0;
            state = 1;
        }
        else if (v[i] > v[i + 1])
        {
            if (i != 0 && state != -1)
                return 0;
            state = -1;
        }
    }

    return state;
}

int main()
{
    int v[] = {1, 1, 1, 1, 1, 1};
    int vN = sizeof(v) / sizeof(v[0]);
    printf("%i\n", sort(v, vN));
    // scanf("%d", &input)
    return 0;
}
