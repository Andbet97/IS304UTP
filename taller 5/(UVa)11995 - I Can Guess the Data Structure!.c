#include <stdio.h>
#include <stdlib.h>

int Heapsize=0;
#define infinito 2147483647

struct respuesta {
  int stack; /*pila*/
  int queue; /*cola*/
  int priorityqueue; /*cola de prioridad*/
  int valor;
};

struct nodo {
  int info;
  struct nodo *sig;
};

struct nodo *Push(struct nodo *p, int elem)
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

struct nodo *Enqueue(struct nodo *p, int elem)
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

int Delete_S_D (struct nodo **p)
{
	int result;
	struct nodo *temp;
	if(*p != NULL)
	{
    if(*p == ((*p)->sig)){
		result=(*p)->info;
		free(*p);
		*p= NULL;
		}
    else{
		temp = (*p)->sig;
		(*p)->sig = temp->sig;
		result=temp->info;
		free(temp);
	  }
	}
	return result;
}

int parent (int i)
{
  return i/2;
}

int left (int i)
{
  return 2*i;
}

int right (int i)
{
  return (2*i)+1;
}

void maxheapify (int *A,int i)
{
  int l, r, least, aux;
  l = left (i);
  r = right (i);
  if ((l <= Heapsize)&&(A[l] > A[i]))
    least = l;
  else
    least = i;
  if ((r <= Heapsize)&&(A[r] > A[least]))
    least = r;
  if (least != i){
    aux = A[i];
    A[i] = A[least];
    A[least] = aux;
    maxheapify (A, least);
  }
  return;
}

int maxPQ_maximum (int *A)
{
  return (A[1]);
}

int maxPQ_Extract (int *A)
{
  int max;
  if (Heapsize < 1){
    return 0;
  }
  else {
    max = maxPQ_maximum (A);
    A[1] = A[Heapsize];
    Heapsize = Heapsize-1;
    maxheapify (A, 1);
    return max;
  }
}

void maxPQ_Decreasekey (int *A, int i, int key)
{
  int aux;
  if (key > A[i]){
    return;
  }
  else {
    A[i] = key;
    while ((i > 1)&&(A[parent (i)] < A[i])){
      aux = A[i];
      A[i] = A[parent (i)];
      A[parent (i)] = aux;
      i = parent (i);
    }
  }
  return;
}

void maxPQ_Insert (int *A, int key)
{
  Heapsize = Heapsize+1;
  A[Heapsize] = infinito;
  maxPQ_Decreasekey (A, Heapsize, key);
  return;
}

int main ()
{
  struct respuesta *a;
  int *minPQ; /*vector de cola de minima prioridad*/
  struct nodo *cola;
  struct nodo *pila;
  int n, i, caso, valor, aux;
  while (scanf("%d", &n) != EOF){
    cola = NULL;
    pila = NULL;
    Heapsize = 0;
    minPQ = (int *)malloc(1006*sizeof(int));
    a = (struct respuesta *)malloc(sizeof(struct respuesta));
    a->queue = 1;
    a->stack = 1;
    a->priorityqueue = 1;
    a->valor = 3;
    for (i = 1; i <= n; i++){
      scanf("%d ", &caso);
      scanf("%d", &valor);
      if (caso == 1){
        if (a->priorityqueue == 1){
          maxPQ_Insert (minPQ, valor);
        }
        if (a->stack == 1){
          pila = Push (pila, valor);
        }
        if (a->queue == 1){
          cola = Enqueue (cola, valor);
        }
      }
      if (caso == 2){
        aux = Delete_S_D (&cola);
        if ((aux != valor)&&(a->queue == 1)){
          a->queue = 0;
          (a->valor)--;
        }
        aux = Delete_S_D (&pila);
        if ((aux != valor)&&(a->stack == 1)){
          a->stack = 0;
          (a->valor)--;
        }
        aux = maxPQ_Extract (minPQ);
        if ((aux != valor)&&(a->priorityqueue == 1)){
          a->priorityqueue = 0;
          (a->valor)--;
          Heapsize = 0;
        }
      }
    }
    if (a->valor == 0){
      printf("impossible\n");
    }
    if (a->valor > 1){
      printf("not sure\n");
    }
    if (a->valor == 1){
      if (a->queue == 1){
        printf("queue\n");
      }
      if (a->stack == 1){
        printf("stack\n");
      }
      if (a->priorityqueue == 1){
        printf("priority queue\n");
      }
    }
    free (a);
    free (cola);
    free (pila);
    free (minPQ);
  }
  return 0;
}
