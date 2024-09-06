# Sort algorithm for [Nakano's CPU](https://github.com/FNakano/OAC1/blob/main/meuProcessador/README.md)

## Table of Contents

- [Introduction](#introduction)
- [Instructions](#instructions)
- [CPU instructions](#cpu-instructions)
- [Code](#code)
- [MEM file](#mem-file)
- [Como foi feito](#como-foi-feito)

## Introduction

This code is a insertion sort algorithm written for the CPU available at [CarregaArmazenaSaltaArit4.circ](https://github.com/FNakano/OAC1/blob/main/meuProcessador/CarregaArmazenaSaltaArit4.circ). This file that can be imported to [Logisim](http://www.cburch.com/logisim/).
More specifications about the CPU can be found in Portuguese at [Nakano's Repository](https://github.com/FNakano/OAC1/blob/main/meuProcessador/Specification.md).

Trabalho feito por:

[Gabriel Monteiro de Souza](https://github.com/SirMonteiro) - 14746450

[Adryelli Reis dos Santos](https://github.com/AdryelliReiz) - 14714019

## Instructions

To test the code, you can open sort.mem and edit "000a" to the number of elements you want to sort in hexadecimal. Then, you can edit the elements you want to sort. The code will sort the elements in ascending order. For the example the worst case scenario for the insertion sort algorithm is used with the values AAAA, AAA9, AAA8 ... AAA1.

After editing the code, with CPU opened in Logisim, you right click the RAM module and select "Load Image..." to load the sort.mem file. Then, you can run the code by enabling ticks inside Simulate->Ticks Enabled.

After it stops run on HALT(0xFFFF) instruction, you right click the RAM module and select "Export Image..." to save the memory with sorted elements.

## CPU instructions

### Load instructions

10FF  LDA  n

10FE  LDA  key

10FD  LDA  j

10FC  LDA  i

10FB  LDA  mask1

10FA  LDA  mask2/LDAvar

10F9  LDA  mask3

10F8  LDA  1

10F7  LDA  STAvar

10F6  LDA  VectorFirstEnd

10F3  LDA  tmp

### Store instructions

20FF  STA  n

20FE  STA  key

20FD  STA  j

20FC  STA  i

20F3  STA  tmp

### Jump instructions

30F3  JMP  tmp

30F5  JMP  HALT

40F5  JNZ  HALT

### Move instructions

6C40  MOV  A, B

6C80  MOV  A, C

6CC0  MOV  A, D

6D80  MOV  A, R

6C08  MOV  B, A

6C10  MOV  C, A

6C18  MOV  D, A

6C38  MOV  PSW, A

6C30  MOV  R, A

### Load constants

6000  LDA  0

6200  LDA  FFFF

### Logical and arithmetic operations

6605  AND  A, A, B  # Generate PSW used to compare

6C05  ADD  A, A, B

6C4F  ADD  B, B, D

6C4C  ADD  B, B, A

6C06  ADD  A, A, C

6C07  ADD  A, A, D

6E06  SUB  A, A, C

6E0E  SUB  A, B, C

663C  AND  A, PSW, A

6C0F  ADD  A, B, D

## Code

This code section is separated in two parts: C code used as a base for the assembly code and the assembly code itself.

### C code

```c

void insertionSort(int arr[], int n)
{
  int key = 0, j = 0, i = 1; // hard coded in mem
  int k = 0; // k var is used to help on simulate non negative numbers

  while (i < n)
  {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
      if (j < 0) {
        j = 0;
        arr[0] = key;
        k = 1;
        break;
      }
    }
    if (!k) arr[j + 1] = key;
    k = 0;
    i = i + 1;
  }
}

```

### Assembly code

For the assembly code, is determined that the array will start at the memory address 0x0100 and the number of elements will be stored at the memory address 0x00FF. i, j, key and n initialization is made hardcoded in the memory.

```assembly
# First while compare
10FC  LDA  i
6C40  MOV  A, B
10FF  LDA  n
6605  AND  A, A, B
10FB  LDA  mask1
663C  AND  PSW, A
40F5  JNZ  HALT

# key = arr[i]
10F6  LDA  firstPos
6CC0  MOV  A, D
6C05  ADD  A, A, B
6C40  MOV  A, B
10FA  LDA  mask2
6C05  ADD  A, A, B
20F3  STA  tmp
30F3  JMP  tmp
20FE  STA  key

# j = i - 1
10F8  LDA  1
6C80  MOV  A, C
10FC  LDA  i
6E06  SUB  A, A, C
20FD  STA  j

# Second while first compare
10FD  LDA  j
6C40  MOV  A, B
6200  LDA  FFFF
6605  AND  A, A, B
10FA  LDA  mask2
663C  AND  A, PSW, A
4036  JNZ  arr[0] = key

# Second while second compare
6C4F  ADD  B, B, D
10FA  LDA  LDAvar
6C05  ADD  A, A, B
20F3  STA  tmp
30F3  JMP  tmp
6C40  MOV  A, B
10FE  LDA  key
6605  AND  A, A, B
10F9  LDA  mask3
663C  AND  A, PSW, A
4039  JNZ  arr[j + 1] = key

# arr[j + 1] = arr[j]
10FD  LDA  j
6C07  ADD  A, A, D
6C06  ADD  A, A, C
6C80  MOV  A, C
10F7  LDA  STAvar
6C06  ADD  A, A, C
20F3  STA  tmp
6C08  MOV  B, A
30F3  JMP  tmp
10F8  LDA  1
6C80  MOV  A, C

# j = j - 1
10FD  LDA  j
6E06  SUB  A, A, C
20FD  STA  j
3015  JMP  Second while first compare

# arr[0] = key, in case of underflow
10FE  LDA  key
2100  STA  arr[0]
3015  JMP  i = i + 1

# arr[j + 1] = key
10FD  LDA  j
6C07  ADD  A, A, D
6C06  ADD  A, A, C
6C40  MOV  A, B
10F7  LDA  STAvar
6C05  ADD  A, A, B
20F3  STA  tmp
10FE  LDA  key
30F3  JMP  tmp

# i = i + 1
10FC  LDA  i
6C06  ADD  A, A, C
20FC  STA  i
3000  JMP  0x000
```

## MEM file

The MEM file is a text file that can be imported to Logisim. It contains the memory address and the value that will be stored in that address. The file is structured as follows:
  - The first line contains the header required for Logisim.
  - The lines 2 to 14 contains the instructions for the CPU.
  - The line 15 contains some constants.
  - The lines 16 contains sort variables including the last that is the number of elements.
  - The lines 17 contains the elements to be sorted.

## Como foi feito

O EP foi inicialmente feito em C comparando alguns algoritmos de ordenação iterativos. O insertion sort foi escolhido por ser um algoritmo simples e aparentemente mais fácil de implementar em assembly. Dessa forma para cada linha em C, foi feita a tradução para as instruções disponíveis em assembly. Para os __loops__ foi implementado da seguinte forma: executa as comparações e caso nao seja verdadeiro, pula para o final das instruções do __loop__. Dessa forma foi-se adaptando algumas lógicas em C, até chegar no estado atual do código em assembly.
