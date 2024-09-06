/*********************************************************************/
/**   ACH2024 - Algoritmo e Estrutura de dados II                   **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 01 - Prof.Dra. Ariane Machado Lima                      **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/**   23/06/2023                                                    **/
/*********************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256 // tamanho máximo do nome do arquivo
#define DEGREE 3         // Grau da árvore B+

typedef int keyType;
typedef struct str_node
{
  keyType key[2 * DEGREE - 1];
  struct str_node *child[2 * DEGREE];
  int numKeys;
  bool isLeaf;
  struct str_node *next;
} NODE;

typedef struct
{
  NODE *root;
} BTREE;

void printBTree(NODE *node)
{
  if (!node)
    return;
  if (node->numKeys == 0)
  {
    printf("Vazia");
    return;
  }

  printf("(");
  for (int i = 0; i < node->numKeys; i++)
  {
    if (!node->isLeaf)
    {
      printBTree(node->child[i]);
      printf(" ");
    }
    printf("%d", node->key[i]);
    if (i < node->numKeys - 1)
      printf(" ");
  }
  if (!node->isLeaf)
    printf(" ");

  printBTree(node->child[node->numKeys]);
  printf(")");
}

NODE *createNode(bool isLeaf)
{
  NODE *node;
  if (!(node = (NODE *)malloc(sizeof(NODE))))
  {
    fprintf(stderr, "[createNode] ERROR - Falha ao alocar %zu bytes.\n", sizeof(NODE));
    return NULL;
  }
  node->isLeaf = isLeaf;
  node->numKeys = 0;
  node->next = NULL;
  for (int i = 0; i < 2 * DEGREE; i++)
    node->child[i] = NULL;
  return node;
}

bool writeToDisk(NODE *node)
{
  return true;
}

bool readFromDisk(NODE *node)
{
  return true;
}

void initializeBTree(BTREE *btree)
{
  NODE *node = createNode(true);
  writeToDisk(node);
  btree->root = node;
}

void splitChild(NODE *parent, int index, NODE *child)
{
  NODE *node = createNode(child->isLeaf);

  if (!child->isLeaf)
  {
    node->numKeys = DEGREE - 1;

    for (int j = 0; j < DEGREE; j++)
    {
      node->child[j] = child->child[j + DEGREE];
    }

    for (int j = 0; j < DEGREE - 1; j++)
    {
      node->key[j] = child->key[j + DEGREE];
    }
  }
  else
  {
    node->numKeys = DEGREE;
    node->next = child->next;
    child->next = node;

    for (int j = 0; j < DEGREE; j++)
    {
      node->key[j] = child->key[j + DEGREE - 1];
    }
  }

  child->numKeys = DEGREE - 1;
  for (int j = parent->numKeys; j >= index + 1; j--)
  {
    parent->child[j + 1] = parent->child[j];
  }
  parent->child[index + 1] = node;
  for (int j = parent->numKeys - 1; j >= index; j--)
  {
    parent->key[j + 1] = parent->key[j];
  }
  parent->key[index] = child->key[DEGREE - 1];
  parent->numKeys++;

  writeToDisk(child);
  writeToDisk(node);
  writeToDisk(parent);
}

void insertNonFull(NODE *node, keyType key)
{
  int i = node->numKeys - 1;
  if (node->isLeaf)
  {
    while (i >= 0 && key < node->key[i])
    {
      node->key[i + 1] = node->key[i];
      i--;
    }
    node->key[i + 1] = key;
    node->numKeys++;
    writeToDisk(node);
  }
  else
  {
    while (i >= 0 && node->key[i] > key)
      i--;
    i++;
    readFromDisk(node->child[i]);
    if (node->child[i]->numKeys == 2 * DEGREE - 1)
    {
      splitChild(node, i, node->child[i]);
      if (key > node->key[i])
        i++;
    }
    insertNonFull(node->child[i], key);
  }
}

void insertBTree(BTREE *btree, keyType key)
{
  NODE *root = btree->root;
  if (root->numKeys == 2 * DEGREE - 1)
  {
    NODE *node = createNode(false);
    btree->root = node;
    node->child[0] = root;
    splitChild(node, 0, root);
    insertNonFull(node, key);
  }
  else
  {
    insertNonFull(root, key);
  }
}

// void removeLeaf(NODE *root, keyType key) {
//   int i = 0;
//   while (i < root->numKeys && root->key[i] < key)
//     i++;

//   for (int j = i; j < root->numKeys - 1; j++)
//     root->key[j] = root->key[j + 1];
//   root->numKeys--;
// }

// void removeSubTree(NODE* root, keyType key) {
//   // printf("Removendo %d com %d\n", key, root->numKeys);
//   int i = 0;
//   while (i < root->numKeys && root->key[i] <= key)
//     i++;

//   printf("%d %d\n", i < root->numKeys, root->key[i] == key);

//   if (i < root->numKeys && root->key[i] == key) {
//     if (root->isLeaf) {
//       removeLeaf(root, key);
//     } else {
//       // removeInternal(root, key);
//     }
//   } else {
//     if (root->child[i]->numKeys >= DEGREE) {
//       if (root->child[i - 1]->numKeys >= DEGREE) {
//         // removeSubTree(root->child[i], key);
//       } else if (root->child[i + 1]->numKeys >= DEGREE) {
//         // removeSubTree(root->child[i], key);
//       } else {
//         // merge(root, i);
//         // removeSubTree(root->child[i], key);
//       }
//     } else if (!root->isLeaf) removeSubTree(root->child[i], key);
//   }
// }

// NODE* findNode(NODE *root, keyType key, NODE **parent, int *index)
// {
//   int i = 0;
//   while (i < root->numKeys && root->key[i] < key)
//     i++;
//   if (!root->isLeaf) {
//     *parent = root;
//     return findNode(root->child[i], key, parent, index);
//   }
//   *index = i;
//   return root;
// }

void removeLeaf(NODE *node, int i)
{
  for (int j = i; j < node->numKeys - 1; j++)
    node->key[j] = node->key[j + 1];
  node->numKeys--;
}

// void removeSubTree(NODE *root, keyType key)
// {
//   NODE *parent = NULL;
//   int i;
//   NODE *node = findNode(root, key, &parent, &i);

//   if (i < node->numKeys && node->key[i] == key) {
//     removeLeaf(node, i);

//     if (node->numKeys < 2 && parent)
//     { // change the 2 to MIN_KEYS
//       // balanceNode(parent, i);
//       if (node->numKeys < DEGREE - 1) {
//         NODE *sibling = parent->child[i - 1];
//         if (sibling->numKeys > DEGREE - 1) {
//           for (int j = node->numKeys; j > 0; j--)
//             node->key[j] = node->key[j - 1];
//           node->key[0] = parent->key[i - 1];
//           parent->key[i - 1] = sibling->key[sibling->numKeys - 1];
//           node->numKeys++;
//           sibling->numKeys--;
//         } else {
//           sibling = parent->child[i + 1];
//           if (sibling->numKeys > DEGREE - 1) {
//             node->key[node->numKeys] = parent->key[i];
//             parent->key[i] = sibling->key[0];
//             for (int j = 0; j < sibling->numKeys - 1; j++)
//               sibling->key[j] = sibling->key[j + 1];
//             node->numKeys++;
//             sibling->numKeys--;
//           } else {
//             // mergeNodes(parent, i);
//             for (int j = i; j < parent->numKeys - 1; j++)
//               parent->key[j] = parent->key[j + 1];
//             parent->numKeys--;
//             parent->child[i] = sibling;
//             free(node);
//           }
//         }
//       }
//     }
//   }
// }

void removeSubTree(NODE *root, keyType key)
{
  int i = 0;

  while (i < root->numKeys && root->key[i] <= key)
    i++;

  if (root->isLeaf)
  {
    // printf("i: [%d] key: %d numKeys: %d\n", i - 1, key, root->numKeys);
    removeLeaf(root, i - 1);
    return;
  }

  if (!root->isLeaf)
  {
    // printf("i: [%d] key: %d numKeys: %d\n", i, key, root->numKeys);
    removeSubTree(root->child[i], key);
  }

  if (root->key[i - 1] == key)
  {
    root->key[i - 1] = root->child[i]->key[0];
  }

  if (root->child[i]->numKeys < DEGREE - 1)
  {
    // printf("Balanceando\n");
    // printf("Balanceando i: %d childKeys: %d\n", i, root->child[i - 1]->numKeys);
    if (i > 0 && root->child[i - 1]->numKeys >= DEGREE)
    {
      // printf("Balanceando com o anterior\n");
      NODE *sibling = root->child[i - 1];
      for (int j = root->child[i]->numKeys; j > 0; j--)
        root->child[i]->key[j] = root->child[i]->key[j - 1];
      root->key[i - 1] = sibling->key[sibling->numKeys - 1];
      root->child[i]->key[0] = root->key[i - 1];
      root->child[i]->numKeys++;
      sibling->numKeys--;
    }
    else if (i < root->numKeys && root->child[i + 1]->numKeys >= DEGREE)
    {
      // printf("Balanceando com o proximo\n");
      NODE *sibling = root->child[i + 1];
      root->child[i]->key[root->child[i]->numKeys] = root->key[i];
      root->key[i] = sibling->key[0];
      for (int j = 0; j < sibling->numKeys - 1; j++)
        sibling->key[j] = sibling->key[j + 1];
      root->child[i]->numKeys++;
      sibling->numKeys--;
    }
    else
    {
      // printf("Merge\n");
      NODE *sibling = root->child[i - 1];

      // sibling->key[sibling->numKeys] = root->key[i - 1];
      for (int j = 0; j < root->child[i]->numKeys; j++)
        sibling->key[sibling->numKeys + j] = root->child[i]->key[j];
      sibling->numKeys += root->child[i]->numKeys;

      for (int j = i - 1; j < root->numKeys - 1; j++)
        root->key[j] = root->key[j + 1];

      sibling->next = root->child[i]->next;
      free(root->child[i]);

      for (int j = i; j < root->numKeys; j++)
        root->child[j] = root->child[j + 1];

      root->numKeys--;
    }
  }

  // NODE *parent = NULL;
  // int i;
  // i = 0;
  // NODE *node = findNode(root, key, &parent, &i);

  // if (i < node->numKeys && node->key[i] == key)
  // {
  //   removeLeaf(node, i);

  //   if (node->numKeys < 2 && parent)
  //   { // change the 2 to MIN_KEYS
  //     // balanceNode(parent, i);
  //     if (node->numKeys < DEGREE - 1)
  //     {

  //     }
  //   }
  // }
}

void removeBTree(BTREE *btree, keyType key)
{
  NODE *root = btree->root;

  if (root->numKeys == 0)
    return;
  removeSubTree(root, key);
  if (root->numKeys == 0 && !root->isLeaf)
  {
    NODE *aux = root->child[0];
    free(root);
    btree->root = aux;
  }
}

int main(int argc, char *argv[])
{
  // verifica a quantidade de argumentos, se for diferente de 3, encerra o programa
  if (argc != 3)
  {
    printf("Uso: %s <arquivo_de_entrada> <arquivo_de_saida>\n",
           argv[0]);
    exit(1);
  }

  // copia o nome do arquivo
  char inputFilename[MAX_FILENAME];
  strcpy(inputFilename, argv[1]);

  char outputFilename[MAX_FILENAME];
  strcpy(outputFilename, argv[2]);

  // Abre o arquivo de entrada, caso nao abra, fecha o programa reportando o erro
  FILE *inputFile = fopen(inputFilename, "r");
  if (!inputFile)
  {
    fprintf(stderr, "[main] ERROR - Falha ao abrir arquivo em \"%s\".\n", inputFilename);
    exit(1);
  }

  // Abre o arquivo de saida, caso nao abra, fecha o programa reportando o erro
  FILE *outputFile = fopen(outputFilename, "w+");
  if (!outputFile)
  {
    fprintf(stderr, "[main] ERROR - Falha ao criar arquivo em \"%s\".\n", outputFilename);
    exit(1);
  }

  // Sobrescreve o padrao de saida para o arquivo
  stdout = outputFile;
  // stderr = fopen("./error.txt", "w+");
  stdin = inputFile;

  BTREE tree;
  initializeBTree(&tree);

  char command[1];
  int key;
  scanf("%c", command);
  while (command[0] != 'f')
  {
    switch (command[0])
    {
    case 'i':
      scanf("%d", &key);
      // printf("Comando i %d\n", key);
      insertBTree(&tree, key);
      break;
    case 'r':
      scanf("%d", &key);
      // printf("Comando r %d\n", key);
      removeBTree(&tree, key);
      break;
    case 'p':
      // printf("Comando p\n");
      printBTree(tree.root);
      printf("\n");
      break;
    }
    scanf("%c", command);
  }

  fclose(inputFile);
  fclose(outputFile);
  // fclose(stderr);
  return 0;
}
