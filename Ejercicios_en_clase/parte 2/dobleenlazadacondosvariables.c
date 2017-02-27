#include <stdio.h>
#include <stdlib.h>

struct nodo{
  int posn;
  int money;
  struct nodo *ant;
  struct nodo *sig;
};

struct nodo *creardoblecircular (int i, int n, int money)
{
  struct nodo *p, *q;
  int r;
  p = NULL;
  for (r=i ; r<=n; r++){
    q = (struct nodo *)malloc(sizeof(struct nodo));
    q->posn = r;
    q->money = money;
    if (p == NULL){
      q->sig = q;
      q->ant = q;
    }
    else {
      q->sig = p->sig;
      p->sig = q;
      q->ant = p;
      (q->sig)->ant = q;
    }
    p = q;
  }
  return p;
}

void imprimir (struct nodo *p)
{
  struct nodo *aux;
  aux = p->sig;
  while (aux != p){/*imprimir en sentido horario +*/
    printf("%d %d+, ", aux->posn, aux->money);
    aux = aux->sig;
  }
  printf("%d %d.\n", aux->posn, aux->money);
  aux = aux->sig;
  while (p != aux){/*imprimir en sentido antihorario -*/
    printf("%d %d-, ", p->posn, p->money);
    p = p->ant;
  }
  printf("%d %d.\n", p->posn, p->money);
  p = p->ant;
  return;
}

int main ()
{
  struct nodo *prueba;
  int n;
  int k;
  scanf ("%d", &k);
  scanf ("%d", &n );
  prueba = creardoblecircular (k, n, 3);
  printf("%d.caso %d.sig %d.ant\n", prueba->posn, (prueba->sig)->posn, (prueba->ant)->posn);
  imprimir (prueba);
  return 0;
}
