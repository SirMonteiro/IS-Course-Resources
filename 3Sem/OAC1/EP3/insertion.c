#include <stdio.h>

void insertionSort(int arr[], int n);

void main()
{
  // int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int arr[] = {9, 8, 7};
  int n = sizeof(arr) / sizeof(arr[0]);

  insertionSort(arr, n);
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void insertionSort(int arr[], int n)
{
  int key, j, i = 1; // hard coded in mem
  int k = 0;

  while (i < n) // first set of instructions
  {
    key = arr[i]; // 2
    j = i - 1; // 3

    while (j >= 0 && arr[j] > key)
    {
      printf("j: %d\n", j);
      arr[j + 1] = arr[j];
      j = j - 1;
      if (j < 0) {
        j = 0;
        arr[0] = key;
        k = 1;
        break;
      }
    }
    if (!k)
    arr[j + 1] = key;
    k = 0;
    i = i + 1;
  }
  printf("i: %d, j: %d, key: %d, n: %d\n", i, j, key, n);
}
