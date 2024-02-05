typedef struct est
{
  int chave;
  int l;
  int c;
  struct est *prox;
} NO;

typedef struct
{
  NO *inicio;
  int maxlin;
  int maxcol;
  int defaultValue;
} MATRIZ;