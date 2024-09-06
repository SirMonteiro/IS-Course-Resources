cpu: 16bits BE
dados: 16 bits
endereço: 12 bits
RAM: 8Kbytes

line 5: mask
line 6: i j key n

perma register: C = 1, D = arr[0]

AAAA AAA9 AAA8 AAA7 AAA6 AAA5 AAA4 AAA3 AAA2 AAA1
AAA1 AAA2 AAA3 AAA4 AAA5 AAA6 AAA7 AAA8 AAA9 AAAA

# Some instructions

10FF - load n var to A
10FE - load key var to A
10FD - load j var to A
10FC - load i var to A
10FB - load mask1 to A
10FA - load mask2/LDAvar to A
10F9 - load mask3 to A
10F8 - load 1 to A
10F7 - load STAvar to A
10F6 - load firstPos to A
10F3 - load tmp var to A

20FF - store A to n var
20FE - store A to key var
20FD - store A to j var
20FC - store A to i var
20F3 - store A to tmp var

6C40 - move A to B
6C80 - move A to C
6CC0 - move A to D
6C08 - move B to A

6000 - load 0 to A
6200 - load FFFF to A

30F3 - jump to tmp
30F3 - jump to HALT
40F3 - jump to HALT if A is different than 0

6605 - A & B // Generate PSW to compare (esta operação é importante para selecionar os bits do PSW a considerar num salto.)

6C05 - A = A + B
6C4F - B = B + D
6C4C - B = B + A
6C06 - A = A + C
6C07 - A = A + D
6E06 - A = A - C
6E0E - A = B - C
663C - A = PSW & A
6C0F - A = B + D

# RAM

### 1while 1compare

10FC - load i var to A
6C40 - move A to B
10FF - load n var to A
6605 - A & B
10FB - load mask1 to A
663C - A = PSW & A
40F5 - jump to HALT if A is different than 0

### key = arr[i];

10F6 - load firstPos to A
6CC0 - move A to D
6C05 - A = A + B
6C40 - move A to B
10FA - load mask2 to A
6C05 - A = A + B
20F3 - store A in tmp
30F3 - jump to tmp
return to next instruction
20FE - store A in key

### j = i - 1;

10F8 - load 1 to A
6C80 - move A to C
10FC - load i var to A
6E06 - A = A - C
20FD - store A to j

### 2while 1compare

10FD - load j to A
6C40 - move A to B
6200 - load FFFF to A
6605 - A & B
10FA - load mask2 to A
663C - A = PSW & A
4036 - jump to finish of first while

### 2while 2compare

6C4F - B = B + D
10FA - load LDAvar to A
6C05 - A = A + B
20F3 - store A to tmp
30F3 - jump to tmp
return to next instruction
6C40 - move A to B
10FE - load key to A
6605 - A & B
10F9 - load mask3 to A
663C - A = PSW & A
4039 - jump to finish of first while after underflow line

### arr[j + 1] = arr[j];

10FD - load j to A
6C07 - A = A + D
6C06 - A = A + C
6C80 - move A to C
10F7 - load stavar to A
6C06 - A = A + C
20F3 - store A to tmp
6C08 - move B to A
30F3 - jump to tmp
return to next instruction
10F8 - load 1 to A
6C80 - move A to C

### j = j - 1

10FD - load j to A
6E06 - A = A - C
20FD - store A to j
3015 - jump to start of second while

## arr[0] = key; incase of underflow

10FE - load key var to A
2100 - store A to arr[0]
3015 - jump to i = i + 1 instruction

### arr[j + 1] = key;

10FD - load j to A
6C07 - A = A + D
6C06 - A = A + C
6C40 - move A to B
10F7 - load stavar to A
6C05 - A = A + B
20F3 - store A to tmp
10FE - load key to A
30F3 - jump to tmp
return to next instruction

### i = i + 1;

10FC - load i to A
6C06 - A = A + C
20FC - store A to i
3000 - jump to start of first while


0110 110 000 000 101
0110 110 001 001 111
0110 110 001 001 100
0110 110 000 000 110
0110 110 000 000 111
0110 111 000 000 110
0110 111 000 001 110

0110 110 000 001 111

0110 000 000 000 000
0110 001 000 000 000
