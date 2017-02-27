#include <stdio.h>
#include <stdlib.h>

#define MAXV 10005
#define Negro 0
#define Blanco 2
#define Gris 1
#define NIL -1

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
int time;

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

void DFS_Visit (int i, int phi[], int D[], int f[], int color[])
{
  struct edge *p;
  color[i] = Gris;
  time = time+1;
  D[i] = time;
  p = G.edge[i];
  while (p != NULL){
    int u;
    u = p->v;
    if (color[u] == Blanco){
      phi[u] = i;
      DFS_Visit (u, phi, D, f, color);
    }
    p = p->next;
  }
  color[i] = Negro;
  time = time+1;
  f[i] = time;
  return;
}

void DFS (int phi[], int D[], int f[])
{
  int i, color[G.nVertex + 2];
  for (i = 1; i <= G.nVertex; i++){
    color[i] = Blanco;
    phi[i] = NIL;
  }
  time = 0;
  for (i = 1; i <= G.nVertex; i++){
    if (color[i] == Blanco){
      DFS_Visit (i, phi, D, f, color);
    }
  }
  return;
}

int solver ()
{
  int i;
  int phi[G.nVertex + 2], D[G.nVertex + 2], f[G.nVertex + 2];
  DFS (phi, D, f);
  int result = 0;
  for (i = 1; i <= G.nVertex; i++){
    if (phi[i] == NIL){
      result++;
    }
  }
  result = ((result-1)*result)/2;
  return result;
}

int main ()
{
  int totalVertex, totalEdges, idVertex, idEdges;
  int vertex1, vertex2, t, i, result;
  struct edge *newNodo;
  scanf("%d", &t);
  for (i = 1; i <= t; i++){
    scanf ("%d %d", &totalVertex, &totalEdges);
    G.nVertex = totalVertex;
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
    result = solver ();
    printf("%d\n", result);
    liberar ();
  }
  return 0;
}
