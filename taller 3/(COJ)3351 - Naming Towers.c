#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
  char info;
  struct nodo *sig;
  struct nodo *ant;
};

struct nodo *crear (char aux[105])
{
  int i;
  struct nodo *cab, *q;
  cab = NULL;
  int l = strlen (aux);
  for (i = 0; i<l; i++){
    q = (struct nodo *)malloc(sizeof(struct nodo));
    q->info = aux[i];
    if (cab == NULL){
      q->sig = q;
      q->ant = q;
      cab = q;
    }
    if (cab != NULL){
      q->sig = cab->sig;
      q->ant = cab;
      (cab->sig)->ant = q;
      cab->sig = q;
      cab = q;
    }
  }
  return cab;
}

int comprobar (struct nodo *p)
{
  int count=0;
  struct nodo *q;
  q = p->sig;
  while (q != p) {
    if ((q->info != 65)&&(q->info != 72)&&(q->info != 73)&&(q->info != 77)&&(q->info != 79)&&(q->info != 84)&&(q->info != 85)&&(q->info != 86)&&(q->info != 87)
        &&(q->info != 88)&&(q->info != 89)){
          count++;
        }
    q = q->sig;
  }
  if ((q->info != 65)&&(q->info != 72)&&(q->info != 73)&&(q->info != 77)&&(q->info != 79)&&(q->info != 84)&&(q->info != 85)&&(q->info != 86)&&(q->info != 87)
      &&(q->info != 88)&&(q->info != 89)){
        count++;
      }
  if (count == 0){
    count = -1;
  }
  return count;
}

int comparar (struct nodo *p, int tam)
{
  int count = 0;
  struct nodo *q, *e;
  q = p->sig;
  if (tam%2 == 1){/*impares*/
    while (p != q){
      if (q->info == p->info)
        count++;
      e = q;
      q = q->sig;
      q->ant = p->ant;
      p->sig = p;
      free (e);
      e = p;
      p = p->ant;
      p->sig = q;
      free (e);
    }
  }
  if (tam%2 == 0){/*pares*/
    while (q->sig != p){
      if (q->info == p->info)
        count++;
      e = q;
      q = q->sig;
      q->ant = p->ant;
      free (e);
      e = p;
      p = p->ant;
      p->sig = q;
      free (e);
    }
    if (q->info == p->info)
      count++;
  }
  if (count == (tam/2)){
    return 1; /*YES*/
  }
  if (count != (tam/2)){
    return -1; /*NO*/
  }
}

int main ()
{
  struct nodo *p;
  int n, i, res, l, res2;
  char aux[105];
  scanf ("%d", &n);
  for (i = 1; i<=n ; i++){
    fflush (stdin);
    scanf ("%s", &aux);
    l = strlen (aux);
    p = crear (aux);
    res = comprobar (p);
    res2 = comparar (p, l);
    if ((res < 0)&&(res2 == 1)){
      printf ("YES\n");
    }
    if ((res > 0)||(res2 == -1)){
      printf ("NO\n");
    }
    p = NULL;
  }
  return 0;
}
