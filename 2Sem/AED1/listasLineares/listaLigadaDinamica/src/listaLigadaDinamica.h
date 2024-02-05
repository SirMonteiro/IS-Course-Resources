typedef struct estrutura
{
    int chave;

    struct estrutura *prox;
} NO;

typedef struct
{
    NO *inicio;
} LISTA_LIG_DIN;

typedef struct
{
    NO *inicio;
    NO *sent;
} LISTA_SENT;