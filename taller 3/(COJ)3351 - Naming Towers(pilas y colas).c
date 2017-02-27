#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
  char info;
  struct nodo *sig;
};

/*operaciones de cola*/

struct nodo *Enqueue(struct nodo *p, int elem) //Ingresar elementos a la cola
{
  struct nodo *q;
  q= (struct nodo*)malloc (sizeof(struct nodo));
  q->info= elem;
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

/*operaciones de pila*/

struct nodo *Push(struct nodo *p, int elem)  //Agregar elementos a la pila
{
    struct nodo *q;
    q= (struct nodo*)malloc (sizeof(struct nodo));
    q->info= elem;
    if(p == NULL)
    {
    q->sig=q;
    p = q;
    }
    else{
    	q->sig = p->sig;
    	p->sig= q;
    }
    return p;
}

/*eliminar de pila y de cola*/

char RmPilayCola (struct nodo **p) //Eliminar elementos de la cola
 {
 	char result;
 	struct nodo *temp;
	if (*p != NULL)
	{
    if(*p == ((*p)->sig)){
		result = (*p)->info;
		free (*p);
		*p= NULL;
		}
    else{
		temp = (*p)->sig;
		(*p)->sig = temp->sig;
		result = temp->info;
		free (temp);
	  }
	}
	return result;
}

/*---------------------*/

int comparar (char V[],int l)
{
  int i;
  int c = 0;
  for (i = 0; i<l; i++){
    if ((V[i] != 65)&&(V[i] != 72)&&(V[i] != 73)&&(V[i] != 77)&&(V[i] != 79)&&(V[i] != 84)&&(V[i] != 85)&&(V[i] != 86)&&(V[i] != 87)&&(V[i] != 88)&&(V[i] != 89)){
          c++;
        }
  }
  if (c == 0)
    return -1;
  return c;
}

int main ()
{
  struct nodo *pila, *cola;
  pila = NULL;
  cola = NULL;
  int n;
  int i, i2, i3;
  int comp = 0;
  int l = 0;
  char V[105];
  char c1, c2;
  scanf ("%d", &n);
  for (i = 1; i<= n; i++){
    fflush (stdin);
    scanf ("%s", &V);
    l = strlen (V);
    comp = comparar(V, l);
    if (comp > 0){
      printf("NO\n");
    }
    else{
      for (i2 = 0; i2<l; i2++){/*crear la pila y cola*/
        pila = Push (pila, V[i2]);
        cola = Enqueue (cola, V[i2]);
      }
      i3 = 0;
      for (i2 = 1; i2<=l; i2++){
        c1 = RmPilayCola (&pila);
        c2 = RmPilayCola (&cola);
        if (c1 == c2)
          i3++;
      }
      if (i3 == l){
        printf("YES\n");
      }
      if (i3 != l){
        printf("NO\n");
      }
    }
  }
  return 0;
}
