#include <stdio.h>
#include <stdlib.h>

#define MAXV 105
#define Negro 0
#define Blanco 2
#define Gris 1
#define NIL -1
#define Infinito 2147483647

struct edge {
  int v;
  struct edge *next;
};

typedef struct {
  struct edge *edge[MAXV+1];
  int nVertex;
  int nEdges;
} graph;

graph G;

void liberar ()
{
  int idVertex;
  struct edge *temp, *temp2;
  for (idVertex = 1; idVertex<= G.nVertex; idVertex++){
    temp2 = G.edge[idVertex];
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
  int idVertex, color[G.nVertex + 2];
  int Q[G.nVertex + 2];
  int headQueue = 1, tailQueue = 1, u, v;
  struct edge *temp;
  for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
    color[idVertex] = Blanco;
    D[idVertex] = Infinito;
    phi[idVertex] = NIL;
  }
  color[s] = Gris;
  D[s] = 0;
  phi[s] = NIL;
  Q[tailQueue] = s;
  tailQueue++;
  while (headQueue != tailQueue){
    u = Q[headQueue];
    headQueue++;
    temp = G.edge[u];
    while (temp != NULL) {
      v = temp->v;
      if (color[v] == Blanco){
        color[v] = Gris;
        D[v] = D[u]+1;
        phi[v] = u;
        Q[tailQueue] = v;
        tailQueue ++;
      }
      temp = temp->next;
    }
    color[u] = Negro;
  }
  return;
}

void solver (int s)
{
  int idVertex;
  int phi[G.nVertex + 2], D[G.nVertex + 2];
  BFS (s, phi, D);
  for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
    printf("minima distancia del vertice de 3 a %d: %d\n", idVertex, D[idVertex]);
    travel (phi, idVertex, s);
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
  scanf ("%d %d", &totalVertex, &totalEdges);
  G.nVertex = totalVertex;
  G.nEdges = totalEdges;
  for (idVertex = 1; idVertex <= G.nVertex; idVertex++){
    G.edge[idVertex] = NULL;
  }
  for (idEdges = 1; idEdges <= G.nEdges; idEdges++){
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
