#include <stdio.h>
#include <stdlib.h>

struct nodo {
  int info;
  struct nodo *sig;
};

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

int josephus (struct nodo *q, int k)
{
  int i, res, n = q->info, residuo;
  struct nodo *p, *r;
  p = q;
  r = p->sig;
  while (r != r->sig){
    residuo = k%n;
    if (residuo == 0)
      residuo =n;
    for (i = 1; i<residuo; i++){
      p = r;
      r = r->sig;
    }
    q = r;
    r = r->sig;
    p->sig = r;
    n--;
    printf("%d, ", q->info);
    free (q);
  }
  res = r->info;
  free (r);
  return res;
}

int main ()
{
  struct nodo *cab;
  cab = crearlistacircular (6);
  printf ("\n%d\n", josephus(cab, 6));
  return 0;
}
