typedef struct s
{
  int chave;
  int bal;
  struct s *esq;
  struct s *dir;
} NO;

typedef struct savl
{
  int chave;
  struct savl *esq;
  struct savl *dir;
  int bal;
} NO_AVL;

typedef struct estruturafila
{
  int chave;
  struct estruturafila *prox;
} NO_FILA;

typedef struct
{
  NO_FILA *inicio;
  NO_FILA *fim;
} FILA;

typedef struct estruturapilha
{
  int chave;
  struct estruturapilha *prox;
} NO_PILHA;

typedef struct
{
  NO_PILHA *topo;
} PILHA;