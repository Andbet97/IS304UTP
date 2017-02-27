#include <stdio.h>
#include <stdlib.h>

#define MAXV 105
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

void travel (int phi[], int d, int s)
{
  if (d == s)
    printf("%d", s);
  else {
    travel (phi, phi[d], s);
    printf(" %d", d);
  }
  return;
}

void BFS (int s, int phi[], int D[])
{
  int i, color[G.nVertex + 2];
  struct nodo *Q;
  int u, v;
  struct edge *temp;
  for (i = 1; i <= G.nVertex; i++){
    color[i] = Blanco;
    D[i] = Infinito;
    phi[i] = NIL;
  }
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
        phi[v] = u;
        Q = Enqueue (Q, v);
      }
      temp = temp->next;
    }
    color[u] = Negro;
  }
  return;
}

void solver (int s)
{
  int i;
  int phi[G.nVertex + 2], D[G.nVertex + 2];
  BFS (s, phi, D);
  printf("\n");
  for (i = 1; i <= G.nVertex; i++){
    printf("minima distancia del vertice 3 a %d: %d\n", i, D[i]);
    travel (phi, i, s);
    printf("\n\n");
  }
  return;
}

void mostrargrafo ()
{
  int idVertex;
  struct edge *temp;
  for (idVertex = 1; idVertex<= G.nVertex; idVertex++){
    printf("Lista de adyacencia del vertice %d: ", idVertex);
    temp = G.edge[idVertex];
    while (temp != NULL){
      printf(" %d", temp->v);
      temp = temp->next;
    }
    printf("\n");
  }
  return;
}

int main ()
{
  int totalVertex, totalEdges, idVertex, idEdges;
  int vertex1, vertex2;
  struct edge *newNodo;
  printf("Ingrese el total de vertices y el total de aristas respectivamente: ");
  scanf ("%d %d", &totalVertex, &totalEdges);
  G.nVertex = totalVertex;
  G.nEdges = totalEdges;
  for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
    G.edge[idVertex] = NULL;
  }
  printf("\nIngrese las aristas:\n", );
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
  mostrargrafo ();
  printf("\n");
  solver (3);
  liberar ();
  return 0;
}
