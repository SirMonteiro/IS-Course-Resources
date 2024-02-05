#include "linearLists.c"

#define COL 10
#define LIN 10

int main()
{
  FILA *fila = (FILA *)malloc(sizeof(FILA));
  PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));

  inicializarFila(fila);
  inicializarPilha(pilha);

  filaInserir(fila, 10);
  pilhaPUSH(pilha, 30);

  filaInserir(fila, 20);
  pilhaPUSH(pilha, 20);

  filaInserir(fila, 30);
  pilhaPUSH(pilha, 10);

  // filaExibir(fila);
  // pilhaExibir(pilha);

  // printf("Fila e pilha iguais?: %d\n", compararFilaEPilha(fila, pilha));

  // catFilaToPilha(fila, pilha);

  // // catPilhaToFila(pilha, fila);

  // filaExibir(fila);
  // pilhaExibir(pilha);

  // LISTA_LIG_DIN *circularSemCabeca = (LISTA_LIG_DIN *)malloc(sizeof(LISTA_LIG_DIN));
  // LISTA_LIG_DIN_CAB *comCabeca = (LISTA_LIG_DIN_CAB *)malloc(sizeof(LISTA_LIG_DIN_CAB));

  // inicializarDIN(circularSemCabeca);
  // inicializarDINCAB(comCabeca);

  // inserir(circularSemCabeca, 10);
  // inserir(circularSemCabeca, 20);
  // inserir(circularSemCabeca, 30);

  // exibir(circularSemCabeca);

  // LISTA_LIG_DIN_CAB *comCabeca = transformarCircularSCabecaEmCabeca(circularSemCabeca);

  // exibirCAB(comCabeca);

  LISTA_LIG_DUP *dupla = (LISTA_LIG_DUP *)malloc(sizeof(LISTA_LIG_DUP));

  // inserir

  return 0;
}