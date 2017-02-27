#include <stdio.h>
#include <stdlib.h>

struct coord {
  int x;
  int y;
};

struct nodo {
  struct coord *posn;
  struct nodo *sig;
};

struct nodo *Enqueue(struct nodo *p, struct coord *pos) /*Ingresar elementos a la cola*/
{
  struct nodo *q;
  q= (struct nodo*)malloc (sizeof(struct nodo));
  q->posn= pos;
  if(p == NULL)
  {
  q->sig=q;
  p=q;
  }
  else{
  	q->sig = p->sig;
  	p->sig= q;
  	p=q;
  }
  return p;
}

struct coord *Dequeue(struct nodo **p) /*Eliminar elementos de la cola*/
 {
 	struct coord *result;
 	struct nodo *temp;
	if (*p != NULL){
    if(*p == ((*p)->sig)){
		result = (*p)->posn;
		free(*p);
		*p= NULL;
		}
    else{
		temp = (*p)->sig;
		(*p)->sig = temp->sig;
    result = temp->posn;
		free(temp);
	  }
	}
	return result;
}

int main ()
{
  int t, x, y, i, aux, i2, result;
  struct nodo *Q;
  Q = NULL;
  struct coord *pos, *temp;
  temp = NULL;
  pos = NULL;
  while (scanf("%d", &t) != EOF){
    for (i = 1; i <= t; i++){
      result = 0;
      scanf("%d %d\n", &x, &y);
      char M[x+1][y+1];
      char in[x];
      for (i2 = 1; i2 <= y; i2++){/*llenado de la matriz*/
        scanf("%s", &in);
        for (aux = 0; aux < x; aux++){
          M[aux+1][i2] = in[aux];
          if (in[aux] == 64){
            pos = (struct coord *)malloc(sizeof(struct coord));
            pos->x = aux+1;
            pos->y = i2;
            Q = Enqueue (Q, pos);
            result++;
            M[aux+1][i2] = 35;
          }
        }
      }
      pos = NULL;
      while (Q != NULL){
        pos = Dequeue (&Q);
        aux = pos->x;
        i2 = pos->y;
        M[aux][i2] = 35;
        if (aux > 1){
          if (M[aux-1][i2] == 46){
            temp = (struct coord *)malloc(sizeof(struct coord));
            temp->x = aux-1;
            temp->y = i2;
            Q = Enqueue (Q, temp);
            result++;
            M[aux-1][i2] = 35;
          }
        }
        if (aux < x){
          if (M[aux+1][i2] == 46){
            temp = (struct coord *)malloc(sizeof(struct coord));
            temp->x = aux+1;
            temp->y = i2;
            Q = Enqueue (Q, temp);
            result++;
            M[aux+1][i2] = 35;
          }
        }
        if (i2 > 1){
          if (M[aux][i2-1] == 46){
            temp = (struct coord *)malloc(sizeof(struct coord));
            temp->y = i2-1;
            temp->x = aux;
            Q = Enqueue (Q, temp);
            result++;
            M[aux][i2-1] = 35;
          }
        }
        if (i2 < y){
          if (M[aux][i2+1] == 46){
            temp = (struct coord *)malloc(sizeof(struct coord));
            temp->y = i2+1;
            temp->x = aux;
            Q = Enqueue (Q, temp);
            result++;
            M[aux][i2+1] = 35;
          }
        }
        free (pos);
        pos = NULL;
      }
      printf("Case %d: %d\n", i, result);
    }
  }
  return 0;
}
