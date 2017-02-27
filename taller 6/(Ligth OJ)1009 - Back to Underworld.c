#include <stdio.h>
#include <stdlib.h>

#define MAXV 20000
#define Negro 0
#define Blanco 2
#define Gris 1
#define NIL -1
#define Infinito 2147483647

struct edge { /*estructura arista, cola*/
  int v;
  struct edge *next;
};

typedef struct {/*estructura grafo*/
  struct edge *edge[MAXV+1]; /*vector de aristas*/
  int nVertex; /*numero de vertices*/
  int nEdges; /*numero de aristas*/
} graph;

graph G;
int total, impares;

struct nodo { /*nodo de la cola*/
  int info;
  struct nodo *sig;
};

struct nodo *Enqueue(struct nodo *p, int elem) /*Ingresar elementos a la cola*/
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

int Dequeue(struct nodo **p) /*Eliminar elementos de la cola*/
 {
 	int result;
 	struct nodo *temp;
	if (*p != NULL)
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

void liberar ()
{
  int i;
  struct edge *temp, *temp2;
  for (i = 1; i <= G.nVertex; i++){
    temp2 = G.edge[i];
    while (temp2 != NULL){
      temp = temp2;
      temp2 = temp2->next;
      free (temp);
    }
    G.edge[i] = NULL;
  }
  return;
}

void BFS (int s, int phi[], int D[], int color[])
{
  struct nodo *Q;
  int u, v;
  struct edge *temp;
  color[s] = Gris;
  D[s] = 0;
  phi[s] = NIL;
  Q = NULL;
  Q = Enqueue (Q, s);
  while (Q != NULL){
    u = Dequeue (&Q);
    temp = G.edge[u];
    while (temp != NULL) {
      v = temp->v;
      if (color[v] == Blanco){
        color[v] = Gris;
        D[v] = D[u]+1;
        total = total+1;
        if ((D[u]+1)%2 == 1)
          impares = impares+1;
        phi[v] = u;
        Q = Enqueue (Q, v);
      }
      temp = temp->next;
    }
    color[u] = Negro;
  }
  return;
}

int solver ()
{
  int i, result, pares;
  result = 0;
  int phi[G.nVertex + 2], D[G.nVertex + 2], color[G.nVertex + 2];
  for (i = 1; i <= G.nVertex; i++){
    color[i] = Blanco;
    D[i] = Infinito;
    phi[i] = NIL;
  }
  for (i = 1; i <= G.nVertex; i++){
    if ((G.edge[i] != NULL)&&(color[i] == Blanco)){
      total = 1;
      impares = 0;
      BFS (i, phi, D, color);
      pares = total-impares;
      if (pares >= impares)
        result += pares;
      else
        result += impares;
    }
  }
  return result;
}

int main ()
{
  int totalVertex, totalEdges, idVertex, idEdges;
  int vertex1, vertex2, t, i;
  struct edge *newNodo;
  scanf("%d", &t);
  for (i = 1; i <= t; i++){
    scanf ("%d", &totalEdges);
    G.nVertex = 20000;
    G.nEdges = totalEdges;
    for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
      G.edge[idVertex] = NULL;
    }
    for (idEdges = 1; idEdges <= G.nEdges; idEdges++){/*esta parte crea la lista de adyacencia*/
      scanf("%d %d", &vertex1, &vertex2);
      newNodo = (struct edge *)malloc(sizeof(struct edge));
      newNodo->v = vertex1;
      if (G.edge[vertex2] != NULL)
        newNodo->next = G.edge[vertex2];
      if (G.edge[vertex2] == NULL)
        newNodo->next = NULL;
      G.edge[vertex2] = newNodo;
      newNodo = (struct edge *)malloc(sizeof(struct edge));
      newNodo->v = vertex2;
      if (G.edge[vertex1] != NULL)
        newNodo->next = G.edge[vertex1];
      if (G.edge[vertex1] == NULL)
        newNodo->next = NULL;
      G.edge[vertex1] = newNodo;
    }
    printf("Case %d: %d\n", i, solver ());
    liberar ();
  }
  return 0;
}
