typedef struct estrutura
{
  int chave;
  struct estrutura *ant;
  struct estrutura *prox;
} NO;

typedef struct estrutura
{
  int chave;
  struct estrutura *prox;
} NO2;

typedef struct
{
  NO *cab;
} LISTA_LIG_DUP_CAB;

typedef struct
{
  NO2 *inicio;
} LISTA_LIG_DUP;