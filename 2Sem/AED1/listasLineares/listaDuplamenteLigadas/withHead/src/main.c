#include "listaDuplamenteLigada.c"

int main()
{
  LISTA_LIG_DUP_CAB *lista = (LISTA_LIG_DUP_CAB *)malloc(sizeof(LISTA_LIG_DUP_CAB));
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