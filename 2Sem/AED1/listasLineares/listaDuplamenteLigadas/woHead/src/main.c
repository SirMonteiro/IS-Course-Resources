#include "listaDuplamenteLigada.c"

int main()
{
  LISTA_LIG_DUP *lista = (LISTA_LIG_DUP *)malloc(sizeof(LISTA_LIG_DUP));
  inicializarLista(lista);

  NO *atual;

  for (int i = 0; i < 10; i++)
  {
    anexarLista(lista, 1 + i);
    if (i == 7)
    {
      atual = lista->cab->ant;
    }
  }
  inserirAntes(lista, 77, atual);
  printf("Lista length: %d\n", listaLength(lista));
  printListaInvertida(lista);
  destroyLista(lista);
  return 0;
}