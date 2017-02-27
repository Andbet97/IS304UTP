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

int josephusdouble (struct nodo *q, int k)
{
  int n = q->info; /*numero de participantes*/
  int i, res, residuo, count=1;
  struct nodo *p, *r;
  p = q;
  r = p->sig;
  while (r != r->sig){
    residuo = k%n;
    if (residuo == 0)
      residuo = n;
    if (count%2 == 1){/*impares -> */
      for (i = 1; i<residuo; i++){
        p = r;
        r = r->sig;
      }
      q = r;
      p = r->ant;
      r = r->sig;
      p->sig = r;
      r->ant = p;
    }
    if (count%2 == 0){/*pares <- */
      for (i = 1; i<residuo; i++){
        p = r;
        r = r->ant;
      }
      q = r;
      p = r->sig;
      r = r->ant;
      r->sig = p;
      p->ant = r;
    }
    q->sig = q;
    q->ant = q;
    n--;
    free (q);
    count++;
  }
  res = r->info;
  free (r);
  return res;
}

int main ()
{
  int n, k;
  int res;
  struct nodo *p;
  while (1 == 1){
    scanf ("%d", &n);
    scanf ("%d", &k);
    if ((n == 0)&&(k == 0))
      break;
    if (n == 1){
      res = 1;
    }
    if (n > 1){
      p = creardoblenlazadacircular (1, n);
      res = josephusdouble (p, k);
    }
    printf ("%d\n", res);
  }
  return 0;
}
