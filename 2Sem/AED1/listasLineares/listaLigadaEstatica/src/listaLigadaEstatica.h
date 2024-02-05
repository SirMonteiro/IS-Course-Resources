#define MAX 100

typedef struct
{
    int chave;
    int prox;
} REGISTROLISTALIGEST;

typedef struct
{
    REGISTROLISTALIGEST A[MAX];
    int inicio;
    int dispo;
} LISTALIGEST;
