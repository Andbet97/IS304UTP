#include <stdio.h>
#include <stdlib.h>

struct nodo {
  int info;
  struct nodo *sig;
  struct nodo *ant;
};

struct nodo *creardoblenlazada (int i, int n)
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

void comparar (struct nodo *s2, int *V, int r, int c)
{
  struct nodo *s1;
  struct nodo *e;
  int count = 0;
  s1 = s2->sig;
  while (s1 != s1->sig){
    for (i = 1; i<=r; i++){
      /*s1*/
      s1=s1->sig;
    }
    for (i = 1; i<=c; i++){
      s2=s2->ant;
      /*s2*/
    }
    if(s1==s2){
      V[count]=s1->info;
      count++;
      e=s1;

      s1=s1->sig;
      s2=s2->ant;
      s2->sig=s1;
      s1->ant=s2;
      free(e);
    }
    else{
      s2=s2->sig;
      s

    }



      s1=s1->sig;
      s2=s2->ant;
      e=s1;



    }


  }
  return;
}

int main ()
{
  int Ganadores[10005];
  int n, r, c;
  struct nodo *p;
  while (1 == 1){
    scanf ("%d %d %d", &n, &r, &c);
    if ((n == 0)&&(r == 0)&&(c == 0))
      break;
    p = creardoblenlazada (1, n);
    comparar (p, &Ganadores, r, c);
    /*ordenar
    imprimir vector*/
  }
}
