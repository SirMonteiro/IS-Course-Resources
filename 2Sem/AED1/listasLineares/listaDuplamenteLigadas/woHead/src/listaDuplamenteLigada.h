typedef struct estrutura
{
  int chave;
  struct estrutura *ant;
  struct estrutura *prox;
} NO;

typedef struct
{
  // NO *cab;
  NO *inicio;
} LISTA_LIG_DUP;