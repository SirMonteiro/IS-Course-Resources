#include <stdlib.h>
#include <stdbool.h>

#include "driverEP1.h"

int processa (short int *M, int memSize) {
  unsigned short int ri, pc, a, b, c, d, r, psw = 0;
  pc=0;
  do {
    ri=M[pc];
    printf("Running the instruction %hx\n", ri);
    switch (ri&0xF000) {
      case 0x0000:
        break;
      case 0x1000:
        a = M[ri & 0x0FFF];
        printf("Loaded to A: %hx\n",a);
        break;
      case 0x2000:
        M[ri & 0x0FFF] = a;
        break;
      case 0x3000:
        // r = M[ri & 0x0FFF] + 1;
        r = pc + 1;
        pc = (ri & 0x0FFF) - 1;
        break;
      case 0x4000:
        if (a != 0) {
          r = pc + 1;
          pc = (ri & 0x0FFF) - 1;
        }
        break;
      case 0x5000:
        short int tmp = pc;
        pc = r - 1;
        r = tmp + 1;
        break;
      case 0x6000:
        unsigned short int *res;
        unsigned short int op1;
        unsigned short int op2;
        bool over = false;
        bool under = false;
        switch (ri & 0x01C0) {
          case 0x0000:
            res = &a;
            break;
          case 0x0040:
            res = &b;
            break;
          case 0x0080:
            res = &c;
            break;
          case 0x00C0:
            res = &d;
            break;
          case 0x0100:
            // res = x;
            break;
          case 0x0140:
            // res = x;
            break;
          case 0x0180:
            res = &r;
            break;
          case 0x01C0:
            res = &psw;
            break;
        }
        switch (ri & 0x0038)
        {
        case 0x0000:
          op1 = a;
          break;
        case 0x0008:
          op1 = b;
          break;
        case 0x0010:
          op1 = c;
          break;
        case 0x0018:
          op1 = d;
          break;
        case 0x0020:
          // op1 = x;
          break;
        case 0x0028:
          // op2 = x;
          break;
        case 0x0030:
          op1 = r;
          break;
        case 0x0038:
          op1 = psw;
          break;
        }
        switch (ri & 0x0007)
        {
        case 0x0004:
          op2 = a;
          break;
        case 0x0005:
          op2 = b;
          break;
        case 0x0006:
          op2 = c;
          break;
        case 0x0007:
          op2 = d;
          break;
        default:
          op2 = 0;
        }
        printf("%hx, %hx [", op1, op2);
        switch (ri & 0x0E00)
        {
        // arit 0x0E00
        // res  0x01C0
        // op1  0x0038
        // op2  0x0007
        case 0x0000:
          *res = 0x0000;
          printf("0");
          break;
        case 0x0200:
          *res = 0xFFFF;
          printf("F");
          break;
        case 0x0400:
          *res = ~op1;
          printf("~");
          break;
        case 0x0600:
          *res = op1 & op2;
          printf("&");
          break;
        case 0x0800:
          *res = op1 | op2;
          printf("|");
          break;
        case 0x0A00:
          *res = op1 ^ op2;
          printf("^");
          break;
        case 0x0C00:
          *res = op1 + op2;
          if (*res > 15) over = true;
          printf("+");
          break;
        case 0x0E00:
          *res = op1 - op2;
          if (*res < 0) under = true;
          printf("-");
          break;
        }
        psw = 0x0088;
        if (over) psw = psw | 0x8000;
        if (under) psw = psw | 0x4000;
        if (op1 < op2) psw = psw | 0x2000;
        if (op1 == op2) psw = psw | 0x1000;
        if (op1 > op2) psw = psw | 0x0800;
        printf("] = %hx. PSW: %hx\n", *res, psw);
        break;
    }
    pc++;
    if (pc>=memSize) pc=0;
  } while ((ri&0xF000)!=0xF000);
}
