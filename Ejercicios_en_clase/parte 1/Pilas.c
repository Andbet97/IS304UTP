#include <stdio.h>
#include <stdlib.h>

struct nodo {
  int info;
  struct nodo *sig;
};


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

int Pop(struct nodo **p)  //ELiminar elementos de la pila
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


int main ()
{
  struct nodo *p;
  int elem,operation;
  p=NULL;
  while(scanf("%d",&operation) != EOF)
  {
  	if(operation == 1)
  	{
  		scanf("%d", &elem);
  		p=Push(p, elem);
	  }
  	if(operation == 2)
  	{
  		if(p==NULL)
  		printf("la pila esta vacia");

  		else
  		printf("%d\n", Pop(&p));
	  }
  }

  return 0;
}
