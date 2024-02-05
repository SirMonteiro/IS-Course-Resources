#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void refazHeapMax(int A[], int i, int n)
{
  int l = 2 * i;
  int r = 2 * i + 1;
  int maior = i;

  if (l <= n && A[l] > A[i])
    maior = l;
  else
    maior = i;

  if (r <= n && A[r] > A[maior])
    maior = r;
  if (maior != i)
  {
    int aux = A[i];
    A[i] = A[maior];
    A[maior] = aux;
    refazHeapMax(A, i, n);
  }
}

void construirMaxHeap(int A[], int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    refazHeapMax(A, i, n);
}

void heapSort(int A[], int n)
{
  construirMaxHeap(A, n);
  for (int i = n - 1; i >= 0; i--)
  {
    int aux = A[i];
    A[i] = A[1];
    A[1] = aux;
    refazHeapMax(A, 1, n);
  }
}

void printVector(int *A, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", A[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  int v[7] = {90, 50, 10, 100, 400, 50, 60};
  // construirMaxHeap(v, 7);
  // printVector(v, 7);
  heapSort(v, 7);
  printVector(v, 7);
  return EXIT_SUCCESS;
}
