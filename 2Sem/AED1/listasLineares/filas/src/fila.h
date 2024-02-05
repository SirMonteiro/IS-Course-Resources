typedef struct estrutura
{
  int chave;
  struct estrutura *prox;
} NO;

typedef struct
{
  NO *inicio;
  NO *fim;
} FILA;