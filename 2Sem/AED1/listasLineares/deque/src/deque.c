#include "deque.h"

bool dequeVazio(DEQUE *d)
{
  if (!d->inicio1)
    return true;
  return false;
}

NO *sairinicio2(DEQUE *d)
{
  if (!d->inicio2)
    return NULL;
  NO *resp = d->inicio2;
  d->inicio2 = d->inicio2->ant;
  if (d->inicio2)
    d->inicio2->prox = NULL;
  else
    d->inicio1 = NULL;
}
