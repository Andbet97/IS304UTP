#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Heapsize=0;

#define MAXV 10005
#define infinito 2147483647
#define inf_max -2147483647
#define NIL -1
#define true 1
#define false 0

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

void maxheapify (struct nodoPQ A[], int i, int positionVertex[])
{
  int l, r, little, positiontemp;
  l = left (i);
  r = right (i);
  struct nodoPQ nodeTemp;
  if ((l <= Heapsize)&&(A[l].distance > A[i].distance))
    little = l;
  else
    little = i;
  if ((r <= Heapsize)&&(A[r].distance > A[little].distance))
    little = r;
  if (little != i){
    positiontemp = positionVertex[A[i].vertex];
    nodeTemp = A[i];
    positionVertex[A[i].vertex] = positionVertex[A[little].vertex];
    A[i] = A[little];
    positionVertex [A[little].vertex] = positiontemp;
    A[little] = nodeTemp;
    maxheapify (A, little, positionVertex);
  }
  return;
}

int ExctractmaxPQ (struct nodoPQ A[], int positionVertex[])
{
  int max = 0;
  if (Heapsize >= 1){
    max = A[1].vertex;
    positionVertex[A[Heapsize].vertex] = 1;
    A[1] = A[Heapsize];
    Heapsize--;
    maxheapify (A, 1, positionVertex);
    return max;
  }
  return 0;
}

void Increasekey (struct nodoPQ A[], int i, int key, int positionVertex[])
{
  int positiontemp;
  struct nodoPQ nodeTemp;
  if (key > A[i].distance){ /*resuelto by andres ramirez (sigo sin entender porque aqui si y en colas de maxima prioridad no)*/
    A[i].distance = key;
    while ((i > 1)&&(A[parent (i)].distance < A[i].distance)){
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

void MaxInsertPQ (struct nodoPQ A[], int key, int vertex, int positionVertex[])
{
  Heapsize = Heapsize+1;
  A[Heapsize].distance = inf_max;
  A[Heapsize].vertex = vertex;
  positionVertex[vertex] = Heapsize;
  Increasekey (A, Heapsize, key, positionVertex);
  return;
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

void Prim_min (int s, int P[], int D[])
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

void Prim_max (int s, int P[], int D[])
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
      MaxInsertPQ(A, 0, idVertex, positionVertex);
      D[idVertex] = 0;
    }
    else {
      MaxInsertPQ(A, inf_max, idVertex, positionVertex);
      D[idVertex] = inf_max;
    }
  }
  while (Heapsize >= 1){
    u = ExctractmaxPQ(A, positionVertex);
    inQueuePQ[u] = false;
    tempEdge = G.edge[u];
    if (D[u] == inf_max)
      break;
    while (tempEdge != NULL){
      v = tempEdge->v;
      weight = tempEdge->weight;
      if ((inQueuePQ[v] == true)&&(D[v] < weight)){
        D[v] = weight;
        P[v] = u;
        Increasekey(A, positionVertex[v], D[v], positionVertex);
      }
      tempEdge = tempEdge->next;
    }
  }
  return;
}

int main ()
{
  int totalVertex, totalEdges, idVertex, idEdges;
  int vertex1, vertex2, i, w, aux, t;
  struct edge *newNodo, *auxiliar;
  scanf("%d", &t);
  for (aux = 1; aux <= t; aux++){
    scanf ("%d", &totalVertex);
    G.nVertex = totalVertex+1;
    for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
      G.edge[idVertex] = NULL;
    }
    totalEdges = 0;
    while (1 == 1){/*esta parte crea la lista de adyacencia*/
      scanf("%d %d %d", &vertex1, &vertex2, &w);
      if ((vertex1 == 0)&&(vertex2 == 0)&&(w == 0))
        break;
      totalEdges++;
      newNodo = (struct edge *)malloc(sizeof(struct edge));
      newNodo->v = vertex1+1;
      newNodo->weight = w;
      if (G.edge[vertex2+1] != NULL)
        newNodo->next = G.edge[vertex2+1];
      if (G.edge[vertex2+1] == NULL)
        newNodo->next = NULL;
      G.edge[vertex2+1] = newNodo;
      newNodo = (struct edge *)malloc(sizeof(struct edge));
      newNodo->v = vertex2+1;
      newNodo->weight = w;
      if (G.edge[vertex1+1] != NULL)
        newNodo->next = G.edge[vertex1+1];
      if (G.edge[vertex1+1] == NULL)
        newNodo->next = NULL;
      G.edge[vertex1+1] = newNodo;
    }
    G.nEdges = totalEdges;
    int P[MAXV + 1], D[MAXV + 1];
    w = 0;
    Prim_min (1, P, D);
    for (i = 1; i <= G.nVertex; i++){
      w += D[i];
    }
    Prim_max (1, P, D);
    for (i = 1; i <= G.nVertex; i++){
      w += D[i];
    }
    if (w%2 == 0)
      printf("Case %d: %d\n", aux, w/2);
    if (w%2 != 0)
      printf("Case %d: %d/2\n", aux, w);
    liberar ();
  }
  return 0;
}
