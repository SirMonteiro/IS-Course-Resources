#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct
{
    int chave;
    // int num; // ...
} REGISTROLISTASEQ;

typedef struct
{
    REGISTROLISTASEQ A[MAX];
    int nroElem;
} LISTASEQ;