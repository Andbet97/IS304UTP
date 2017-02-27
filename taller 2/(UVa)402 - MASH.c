#include <stdio.h>
#include <stdlib.h>

struct nodo {
  int info;
  struct nodo *sig;
};

struct nodo *crearlista (int n)
{
  struct nodo *p, *q;
  p = NULL;
  while (n>0){
    q = (struct nodo *)malloc(sizeof(struct nodo));
    q->info = n;
    q->sig = p;
    p = q;
    n--;
  }
  return p;
}

struct nodo *eliminarlista (struct nodo *cab, int c, int n, int x)
{
  int i =1;
  struct nodo *p, *r;
  p = cab;
  r = NULL;
  while (p != NULL){
    if (n == x)
      break;
    if (i%c == 0){
    	n--;
      if (p == cab){
        cab = cab->sig;
        free (p);
        p = cab;
      }
      if (p->sig == NULL){
          free (p);
          r->sig = NULL;
          p = r->sig;
      }
      if ((r != NULL)&&(p != NULL)){
        r->sig = p->sig;
        free(p);
        p = r->sig;
      }
	  }
    else {
      r = p;
      p = p->sig;
    }
    i++;
  }
  return cab;
}

void imprimir (struct nodo *cab)
{
  struct nodo *p;
  p = cab;
  while (p != NULL){
    printf ("%d ", p->info);
    p = p->sig;
  }
  return;
}

int contarelemetos (struct nodo *cab)
{
  int res = 0;
  while (cab != NULL){
    res++;
    cab = cab->sig;
  }
  return res;
}

void liberar (struct nodo *cab)
{
  struct nodo *q;
  q = cab;
  while (q != NULL){
    cab = q;
    q = q->sig;
    free (cab);
  }
  return;
}

int main ()
{
  struct nodo *cab;
  int n = 0;
  int x = 0;
  int i = 0;
  int cont = 1;
  int V[25];
  while (scanf ("%d", &n) != EOF){
    scanf ("%d", &x);
    for (i=1; i<=20; i++)
      scanf ("%d", &V[i]);
    cab = crearlista (n);
    for (i = 1; n > x; i++){
      if (V[i] < n){
        cab = eliminarlista (cab, V[i], n, x);
        n = contarelemetos (cab);
      }
      if (i == 20)
        i = 0;
    }
    printf ("Selection #%d\n", cont);
    imprimir (cab);
    printf("\n\n");
    cont++;
    liberar(cab);
  }
  return 0;
}
