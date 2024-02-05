typedef struct estruturaNO
{
  int chave;
  struct estruturaNO *prox;
} NO;

typedef struct estruturaNODUP
{
  int chave;
  struct estruturaNODUP *ant;
  struct estruturaNODUP *prox;
} NO_DUP;

typedef struct estruturaNOMATRIZ
{
  int chave;
  int l;
  int c;
  struct estruturaNOMATRIZ *prox;
} NO_MATRIZ;

typedef struct
{
  NO *inicio;
} LISTA_LIG_DIN;

typedef struct
{
  NO *cab;
} LISTA_LIG_DIN_CAB;

typedef struct
{
  NO *inicio;
  NO *sent;
} LISTA_LIG_SENT;

typedef struct
{
  NO_DUP *cab;
} LISTA_LIG_DUP_CAB;

typedef struct
{
  NO_DUP *inicio;
} LISTA_LIG_DUP;

typedef struct
{
  NO *inicio;
  NO *fim;
} FILA;

typedef struct
{
  NO *topo;
} PILHA;

typedef struct
{
  NO *inicio;
  int maxlin;
  int maxcol;
  int defaultValue;
} MATRIZ;
