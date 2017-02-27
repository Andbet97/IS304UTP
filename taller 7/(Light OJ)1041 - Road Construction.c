#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Heapsize=0;

#define MAXV 10002
#define infinito 2147483647
#define NIL -1
#define true 1
#define false 0

struct list {
  char cadena[52];
  int numero;
  struct list *sig;
};

struct nodoPQ {
  int vertex;
  int distance;
};

struct edge {
  int v;
  int weight;
  struct edge *next;
};

typedef struct {
  struct edge *edge[MAXV+1];
  int nVertex;
  int nEdges;
} graph;

graph G;

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

void minheapify (struct nodoPQ A[], int i, int positionVertex[])
{
  int l, r, little, positiontemp;
  l = left (i);
  r = right (i);
  struct nodoPQ nodeTemp;
  if ((l <= Heapsize)&&(A[l].distance < A[i].distance))
    little = l;
  else
    little = i;
  if ((r <= Heapsize)&&(A[r].distance < A[little].distance))
    little = r;
  if (little != i){
    positiontemp = positionVertex[A[i].vertex];
    nodeTemp = A[i];
    positionVertex[A[i].vertex] = positionVertex[A[little].vertex];
    A[i] = A[little];
    positionVertex [A[little].vertex] = positiontemp;
    A[little] = nodeTemp;
    minheapify (A, little, positionVertex);
  }
  return;
}

int ExctractminPQ (struct nodoPQ A[], int positionVertex[])
{
  int min = 0;
  if (Heapsize >= 1){
    min = A[1].vertex;
    positionVertex[A[Heapsize].vertex] = 1;
    A[1] = A[Heapsize];
    Heapsize--;
    minheapify (A, 1, positionVertex);
    return min;
  }
  return 0;
}

void Decreasekey (struct nodoPQ A[], int i, int key, int positionVertex[])
{
  int positiontemp;
  struct nodoPQ nodeTemp;
  if (key <= A[i].distance){
    A[i].distance = key;
    while ((i > 1)&&(A[parent (i)].distance > A[i].distance)){
      positiontemp = positionVertex[A[i].vertex];
      nodeTemp = A[i];
      positionVertex[A[i].vertex] = positionVertex[A[parent (i)].vertex];
      A[i] = A[parent (i)];
      positionVertex[A[parent (i)].vertex] = positiontemp;
      A[parent (i)] = nodeTemp;
      i = parent (i);
    }
  }
  return;
}

void MinInsertPQ (struct nodoPQ A[], int key, int vertex, int positionVertex[])
{
  Heapsize = Heapsize+1;
  A[Heapsize].distance = infinito;
  A[Heapsize].vertex = vertex;
  positionVertex[vertex] = Heapsize;
  Decreasekey (A, Heapsize, key, positionVertex);
  return;
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

void Prim (int s, int P[], int D[])
{
  int idVertex, u, v, weight;
  struct nodoPQ A[MAXV + 1];
  int positionVertex[MAXV + 1];
  int inQueuePQ[MAXV + 1];
  struct edge *tempEdge;
  Heapsize = 0;
  for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
    P[idVertex] = NIL;
    inQueuePQ[idVertex] = true;
    if (idVertex == s){
      MinInsertPQ(A, 0, idVertex, positionVertex);
      D[idVertex] = 0;
    }
    else {
      MinInsertPQ(A, infinito, idVertex, positionVertex);
      D[idVertex] = infinito;
    }
  }
  while (Heapsize >= 1){
    u = ExctractminPQ(A, positionVertex);
    inQueuePQ[u] = false;
    tempEdge = G.edge[u];
    if (D[u] == infinito)
      break;
    while (tempEdge != NULL){
      v = tempEdge->v;
      weight = tempEdge->weight;
      if ((inQueuePQ[v] == true)&&(D[v] > weight)){
        D[v] = weight;
        P[v] = u;
        Decreasekey(A, positionVertex[v], D[v], positionVertex);
      }
      tempEdge = tempEdge->next;
    }
  }
  return;
}

int busqueda (struct list *nombres, char cadena[])
{
  int posn = 0;
  struct list *p;
  p = nombres;
  while (p != NULL){
    if (strcmp(p->cadena, cadena) == 0)
      posn = p->numero;
    p = p->sig;
  }
  return posn;
}

struct edge *buscarlista (struct edge *lista, int vertex)
{
  struct edge *result = NULL;
  struct edge *p;
  p = lista;
  while (p != NULL){
    if (p->v == vertex)
      result = p;
    p = p->next;
  }
  return result;
}

int main ()
{
  struct list *nombres, *p;
  nombres = NULL;
  int totalEdges, idVertex, idEdges;
  int vertex1, vertex2, i, w, t, aux, i2, c;
  char cadena[52], cadena2[52];
  struct edge *newNodo, *auxiliar;
  scanf("%d", &t);
  for (i = 1; i <= t; i++){
    int P[MAXV + 1], D[MAXV + 1];
    scanf ("%d", &totalEdges);
    G.nVertex = 10002;
    G.nEdges = totalEdges;
    for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
      G.edge[idVertex] = NULL;
    }
    aux = 0;
    for (idEdges = 1; idEdges <= G.nEdges; idEdges++){/*esta parte crea la lista de adyacencia*/
      scanf("%s %s %d", &cadena, &cadena2, &w);
      if (nombres == NULL){
        p = (struct list *)malloc(sizeof(struct list));
        aux++;
        strcpy (p->cadena, cadena);
        p->numero = aux;
        p->sig = NULL;
        nombres = p;
      }
      if (nombres != NULL) {
        c = busqueda (nombres, cadena);
        if (c != 0){
          vertex1 = c;
        }
        if (c == 0){
          p = (struct list *)malloc(sizeof(struct list));
          aux++;
          strcpy (p->cadena, cadena);
          p->numero = aux;
          p->sig = nombres;
          nombres = p;
          vertex1 = aux;
        }
        c = busqueda (nombres, cadena2);
        if (c != 0){
          vertex2 = c;
        }
        if (c == 0){
          p = (struct list *)malloc(sizeof(struct list));
          aux++;
          strcpy (p->cadena, cadena2);
          p->numero = aux;
          p->sig = nombres;
          nombres = p;
          vertex2 = aux;
        }
      }
      c = 0;
      if (G.edge[vertex2] == NULL){
        newNodo = (struct edge *)malloc(sizeof(struct edge));
        newNodo->v = vertex1;
        newNodo->weight = w;
        newNodo->next = NULL;
        G.edge[vertex2] = newNodo;
        c++;
      }
      if ((G.edge[vertex2] != NULL)&&(c == 0)){
        auxiliar = buscarlista(G.edge[vertex2], vertex1);
        if (auxiliar == NULL){
          newNodo = (struct edge *)malloc(sizeof(struct edge));
          newNodo->v = vertex1;
          newNodo->weight = w;
          newNodo->next = G.edge[vertex2];
          G.edge[vertex2] = newNodo;
        }
        if (auxiliar != NULL){
          if (w < auxiliar->weight)
            auxiliar->weight = w;
        }
      }
      c = 0;
      if (G.edge[vertex1] == NULL){
        newNodo = (struct edge *)malloc(sizeof(struct edge));
        newNodo->v = vertex2;
        newNodo->weight = w;
        newNodo->next = NULL;
        G.edge[vertex1] = newNodo;
        c++;
      }
      if ((G.edge[vertex1] != NULL)&&(c == 0)){
        auxiliar = buscarlista(G.edge[vertex1], vertex2);
        if (auxiliar == NULL){
          newNodo = (struct edge *)malloc(sizeof(struct edge));
          newNodo->v = vertex2;
          newNodo->weight = w;
          newNodo->next = G.edge[vertex1];
          G.edge[vertex1] = newNodo;
        }
        if (auxiliar != NULL){
          if (w < auxiliar->weight)
            auxiliar->weight = w;
        }
      }
    }
    G.nVertex = aux;
    Prim (1, P, D);
    w = 0;
    for (i2 = 1; i2 <= G.nVertex; i2++){
      if (P[i2] == NIL)
        w++;
    }
    if (w == 1){
      c = 0;
      for (i2 = 1; i2 <= G.nVertex; i2++){
        c = c+D[i2];
      }
      printf("Case %d: %d\n", i, c);
    }
    else {
      printf("Case %d: Impossible\n", i);
    }
    liberar ();
    p = nombres->sig;
    while (p != NULL){
      free (nombres);
      nombres = p;
      p = p->sig;
    }
    free (nombres);
    nombres = NULL;
  }
  return 0;
}
