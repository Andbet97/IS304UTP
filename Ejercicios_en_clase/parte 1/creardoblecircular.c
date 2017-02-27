#include <stdio.h>
#include <stdlib.h>

struct nodo{
  int info;
  struct nodo *ant;
  struct nodo *sig;
};

struct nodo *creardoblenlazadacircular (int i, int n)
{
  struct nodo *p, *q;
  int r;
  p = NULL;
  for (r=i ; r<=n; r++){
    q = (struct nodo *)malloc(sizeof(struct nodo));
    q->info = r;
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
    printf("%d+, ", aux->info);
    aux = aux->sig;
  }
  printf("%d.\n", aux->info);
  aux = aux->sig;
  while (p != aux){/*imprimir en sentido antihorario -*/
    printf("%d-, ", p->info);
    p = p->ant;
  }
  printf("%d.\n", p->info);
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
  prueba = creardoblenlazadacircular (k, n);
  printf("%d.caso %d.sig %d.ant\n", prueba->info, prueba->sig, prueba->ant);
  imprimir (prueba);
  return 0;
}
