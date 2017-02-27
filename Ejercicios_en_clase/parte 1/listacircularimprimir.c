#include <stdio.h>
#include <stdlib.h>

struct nodo {
  int info;
  struct nodo *sig;
};

void imprimircircular (struct nodo *cab)
{
  struct nodo *p, *q;
  q = cab->sig;
  p = NULL;
  if (cab != NULL){
    while (p != cab){
      printf ("%d ", q->info);
      p = q;
      q = q->sig;
    }
    printf("\n");
  }
  else
    printf("La lista esta vacia.\n");
  return;
}

struct nodo *crearlistacircular (int n)
{
  struct nodo *p, *q;
  int i;
  p = NULL;
  for (i = 1; i<=n; i++){
    q = (struct nodo *)malloc(sizeof(struct nodo));
    q->info =i;
    if (p == NULL){
      q->sig = q;
      p = q;
    }
    else {
      q->sig = p->sig;
      p->sig = q;
      p = q;
    }
  }
  return p;
}

int main ()
{
  struct nodo *cab;
  cab = crearlistacircular (10);
  imprimircircular (cab);
  return 0;
}
