#include <stdio.h>
#include <stdlib.h>

struct coord {
  int x;
  int y;
  int z;
  int d;
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
  int z, x, y, i, aux, i2, dis, result;
  struct nodo *Q;
  Q = NULL;
  struct coord *pos, *temp;
  temp = NULL;
  pos = NULL;
  while (1 == 1){
    scanf("%d ", &z);
    scanf("%d ", &y);
    scanf("%d", &x);
    if ((z == 0)&&(y == 0)&&(x == 0)){
      break;
    }
    int realY = z*y;
    char M[x+1][realY+1];
    char in[x];
    for (i2 = 0, i = 1; i <= realY; i++){
      if ((i-1)%y == 0)
        i2++;
      scanf("%s", &in);
      for (aux = 0; aux < x; aux++){
        M[aux+1][i] = in[aux];
        if (M[aux+1][i] == 83){
          pos = (struct coord *)malloc(sizeof(struct coord));
          pos->x = aux+1;
          pos->y = i;
          pos->z = i2;
          pos->d = 0;
          Q = Enqueue (Q, pos);
        }
      }
    }
    pos = NULL;
    result = 0;
    while (Q != NULL){
      if (result != 0)
        break;
      pos = Dequeue (&Q);
      i = pos->x;
      i2 = pos->y;
      aux = pos->z;
      dis = pos->d;
      if (i > 1){
        if (M[i-1][i2] == 46){
          temp = (struct coord *)malloc(sizeof(struct coord));
          temp->x = i-1;
          temp->y = i2;
          temp->z = aux;
          temp->d = dis+1;
          Q = Enqueue (Q, temp);
          M[i-1][i2] = 83;
        }
        if (M[i-1][i2] == 69){
          result = dis+1;
        }
      }
      if (i < x){
        if (M[i+1][i2] == 46){
          temp = (struct coord *)malloc(sizeof(struct coord));
          temp->x = i+1;
          temp->y = i2;
          temp->z = aux;
          temp->d = dis+1;
          Q = Enqueue (Q, temp);
          M[i+1][i2] = 83;
        }
        if (M[i+1][i2] == 69){
          result = dis+1;
        }
      }
      if (i2 > ((aux*y)-y)+1){
        if (M[i][i2-1] == 46){
          temp = (struct coord *)malloc(sizeof(struct coord));
          temp->x = i;
          temp->y = i2-1;
          temp->z = aux;
          temp->d = dis+1;
          Q = Enqueue (Q, temp);
          M[i][i2-1] = 83;
        }
        if (M[i][i2-1] == 69){
          result = dis+1;
        }
      }
      if (i2 < aux*y){
        if (M[i][i2+1] == 46){
          temp = (struct coord *)malloc(sizeof(struct coord));
          temp->x = i;
          temp->y = i2+1;
          temp->z = aux;
          temp->d = dis+1;
          Q = Enqueue (Q, temp);
          M[i][i2+1] = 83;
        }
        if (M[i][i2+1] == 69){
          result = dis+1;
        }
      }
      if ((aux >= 1)&&(aux < z)){
        if (M[i][i2+y] == 46){
          temp = (struct coord *)malloc(sizeof(struct coord));
          temp->x = i;
          temp->y = i2+y;
          temp->z = aux+1;
          temp->d = dis+1;
          Q = Enqueue (Q, temp);
          M[i][i2+y] = 83;
        }
        if (M[i][i2+y] == 69){
          result = dis+1;
        }
      }
      if ((aux <= z)&&(aux > 1)){
        if (M[i][i2-y] == 46){
          temp = (struct coord *)malloc(sizeof(struct coord));
          temp->x = i;
          temp->y = i2-y;
          temp->z = aux-1;
          temp->d = dis+1;
          Q = Enqueue (Q, temp);
          M[i][i2-y] = 83;
        }
        if (M[i][i2-y] == 69){
          result = dis+1;
        }
      }
      free (pos);
      pos = NULL;
    }
    if (Q != NULL){
      while (Q != NULL) {
        pos = Dequeue (&Q);
        free (pos);
        pos = NULL;
      }
    }
    if (result == 0)
      printf("Trapped!\n");
    if (result != 0)
      printf("Escaped in %d minute(s).\n", result);
  }
  return 0;
}
