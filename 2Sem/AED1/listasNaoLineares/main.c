void preOrder(NO *raiz) {
  PILHA p *;
  inicializarPilha(&pi);
  NO *p = raiz;
  while (true) {
    while (p) {
      visitar(p);
      if (p->dir)
        push(&push, p->dir);
    }
    p = p->esq;
    p = pop(&p);
    if (!p)
      break;
  }
}

void preOrdem(p) {
  if (p) {
    visitar(p);
    preOrdem(p->esq);
    preOrdem(p->dir);
  }
}

void contar(NO *p, int *resp) {
  if (p) {
    *resp = *resp + 1;
    contar(p->esq, resp);
    contar(p->dir, resp);
  }
}

int contar2(NO *p) {
  if (!p)
    return 0;
  else {
    return 1 + contar2(p->esq) + contar2(p->dir);
  }
}

int max(int a, int b) { return (a > b) ? a : b; }

int altura(NO *p) {
  if (!p)
    return 0;
  if (!p->esq && !p->dir)
    return 1;
  return 1 + max(altura(p->esq), altura(p->dir));
}

void busca(NO *p, int ch, NO **resp) {
  if (p) {
    if (p->chave == ch)
      *resp = p;
    if (*resp == NULL)
      busca(p->esq, ch, resp);
    if (*resp == NULL)
      busca(p->dir, ch, resp);
  }
}

NO *copia(NO *p) {
  if (!p)
    return NULL;
  NO *novo = (NO *)malloc(sizeof(NO));
  novo->chave = p->chave;
  novo->esq = copia(p->esq);
  novo->dir = copia(p->dir);
  return novo;
}
