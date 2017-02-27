#include <stdio.h>
#include <stdlib.h>

struct nodo{
  int info;
  struct nodo *sig;
};

struct nodo *crearlistacircular (int n)
{
  struct nodo *p, *q;
  int i;
  p = NULL;
  for (i = 2; i<=n; i++){
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

int scheme (struct nodo *q, int k)
{
  int i, res, n = (q->info)-1, residuo;
  struct nodo *p, *r;
  p = q;
  r = p->sig;
  while (r != r->sig){
    residuo = k%n;
    if (residuo == 0)
      residuo = n;
    for (i = 1; i<residuo; i++){
      p = r;
      r = r->sig;
    }
    q = r;
    r = r->sig;
    p->sig = r;
    q->sig = q;
    n--;
    free (q);
  }
  res = r->info;
  free (r);
  return res;
}

int main ()
{
  struct nodo *p;
  int n, i, m;
  while (1 == 1){
    scanf ("%d", &n);
    if (n == 0){
      break;
    }
    if ((n < 13)||(n >=100))
      break;
    if (n == 13){
      printf ("1\n");
    }
    if (n > 13){
      for(m = 2; i!=13; m++){
        p = crearlistacircular (n);
        i = scheme (p, m);
      }
      printf ("%d\n", m-1);
      i = 0;
    }
  }
  return 0;
}
