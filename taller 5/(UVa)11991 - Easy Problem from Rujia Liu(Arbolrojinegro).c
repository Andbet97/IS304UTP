#include <stdio.h>
#include <stdlib.h>

#define NIL -2147483647
#define Negro 78
#define Rojo 82

struct nodoRBTree{
  int key;
  char color;
  int posn;
  struct nodoRBTree *p;
  struct nodoRBTree *right;
  struct nodoRBTree *left;
};

struct nodoRBTree *Asg_NIL ()
{
  struct nodoRBTree *x;
  x = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
  x->p = NULL;
  x->right = NULL;
  x->left = NULL;
  x->color = Negro;
  x->posn = NIL;
  x->key = NIL;
  return x;
}

struct nodoRBTree *Treesearch (struct nodoRBTree *x, int k)
{
	while ((x->key != NIL)&&(k != x->key)){
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

struct nodoRBTree *Treemin (struct nodoRBTree *T)
{
	struct nodoRBTree *x;
	x = T;
	while ((x->left)->key != NIL){
		x = x->left;
	}
	return x;
}

struct nodoRBTree *sucessor (struct nodoRBTree *x)
{
	struct nodoRBTree *y;
	if ((x->right)->key != NIL){
		return Treemin (x->right);
	}
	y = x->p;
	while ((y->key != NIL)&&(x == y->right)) {
		x = y;
		y = y->p;
	}
	return y;
}

struct nodoRBTree *leftRotate (struct nodoRBTree *T, struct nodoRBTree *x)
{
  struct nodoRBTree *y;
  y = x->right;
  x->right = y->left;
  (y->left)->p = x;
  y->p = x->p;
  if ((x->p)->key == NIL)
    T = y;
  else {
    if (x == (x->p)->left)
      (x->p)->left = y;
    else
      (x->p)->right = y;
  }
  y->left = x;
  x->p = y;
  return T;
}

struct nodoRBTree *rightRotate (struct nodoRBTree *T, struct nodoRBTree *x)
{
  struct nodoRBTree *y;
  y = x->left;
  x->left = y->right;
  (y->right)->p = x;
  y->p = x->p;
  if ((x->p)->key == NIL)
    T = y;
  else {
    if (x == (x->p)->right)
      (x->p)->right = y;
    else
      (x->p)->left = y;
  }
  y->right = x;
  x->p = y;
  return T;
}

struct nodoRBTree *RB_insert_fixup (struct nodoRBTree *T, struct nodoRBTree *z)
{
  struct nodoRBTree *y;
  while ((z->p)->color == Rojo){
    if (z->p == ((z->p)->p)->left){
      y = ((z->p)->p)->right;
      if (y->color == Rojo){
        (z->p)->color = Negro;
        y->color = Negro;
        ((z->p)->p)->color = Rojo;
        z = (z->p)->p;
      }
      else {
        if (z == (z->p)->right){
          z = z->p;
          T = leftRotate (T, z);
        }
        (z->p)->color = Negro;
        ((z->p)->p)->color = Rojo;
        T = rightRotate (T, (z->p)->p);
      }
    }
    else {
      y = ((z->p)->p)->left;
      if (y->color == Rojo){
        (z->p)->color = Negro;
        y->color = Negro;
        ((z->p)->p)->color = Rojo;
        z = (z->p)->p;
      }
      else {
        if (z == (z->p)->left){
          z = z->p;
          T = rightRotate (T, z);
        }
        (z->p)->color = Negro;
        ((z->p)->p)->color = Rojo;
        T = leftRotate (T, (z->p)->p);
      }
    }
  }
  T->color = Negro;
  return T;
}

struct nodoRBTree *RB_insert (struct nodoRBTree *T, struct nodoRBTree *z)
{
  struct nodoRBTree *x, *y;
  if (T->key == NIL)
    y = T;
  x = T;
  while (x->key != NIL) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  free (z->p);
  z->p = y;
  if (y->key == NIL)
    T = z;
  else{
    if (z->key < y->key){
      free (y->left);
      y->left = z;
    }
    else{
      free (y->right);
      y->right = z;
    }
  }
  return RB_insert_fixup (T, z);
}

struct nodoRBTree *RB_delete_fixup (struct nodoRBTree *T, struct nodoRBTree *x)
{
  struct nodoRBTree *w;
  while ((x != T)&&(x->color == Negro)){
    if (x == (x->p)->left){
      w = (x->p)->right;
      if (w->color == Rojo){
        w->color = Negro;
        (x->p)->color = Rojo;
        T = leftRotate (T, x->p);
        w = (x->p)->right;
      }
      if (((w->left)->color == Negro)&&((w->right)->color == Negro)){
        w->color = Rojo;
        x = x->p;
      }
      else {
        if ((w->right)->color == Negro){
          (w->left)->color = Negro;
          w->color = Rojo;
          T = rightRotate (T, w);
          w = (x->p)->right;
        }
        w->color = (x->p)->color;
        (x->p)->color = Negro;
        (w->right)->color = Negro;
        T = leftRotate (T, x->p);
        x = T;
      }
    }
    else {
      w = (x->p)->left;
      if (w->color == Rojo){
        w->color = Negro;
        (x->p)->color = Rojo;
        T = rightRotate (T, x->p);
        w = (x->p)->left;
      }
      if (((w->right)->color == Negro)&&((w->left)->color == Negro)){
        w->color = Rojo;
        x = x->p;
      }
      else {
        if ((w->left)->color == Negro){
          (w->right)->color = Negro;
          w->color = Rojo;
          T = leftRotate (T, w);
          w = (x->p)->left;
        }
        w->color = (x->p)->color;
        (x->p)->color = Negro;
        (w->left)->color = Negro;
        T = rightRotate (T, x->p);
        x = T;
      }
    }
  }
  x->color = Negro;
  return T;
}

struct nodoRBTree *RB_delete (struct nodoRBTree *T, struct nodoRBTree *z)
{
  struct nodoRBTree *x, *y;
  if (((z->left)->key == NIL)||((z->right)->key == NIL))
    y = z;
  else
    y = sucessor (z);
  if ((y->left)->key != NIL)
    x = y->left;
  else
    x = y->right;
  x->p = y->p;
  if ((y->p)->key == NIL)
    T = x;
  else {
    if (y == (y->p)->left)
      (y->p)->left = x;
    else
      (y->p)->right = x;
  }
  if (y != z)
    z->key = y->key;
  if (y->color == Negro)
    T = RB_delete_fixup (T, x);
  /******************************************************************************************/
                                  /*Liberar el nodo a borrar*/
  if ((y->right)->p == y)/*si el hijo por la derecha lo sigue reconociendo como padre*/
    free (y->right);
  if ((y->left)->p == y)/*si el hijo por la izquierda lo sigue reconociendo como padre*/
    free (y->left);
  free (y);
  /*******************************************************************************************/
  if (T->key == NIL){
    free (T->p);
    T->p = NULL;
  }
  return T;
}

void freeTree (struct nodoRBTree *A, int x)
{
  struct nodoRBTree *z;
  int i;
  for (i = 1; i <= x; i++){
    z = Treesearch (A, i);
    A = RB_delete (A, z);
  }
  free (A);
  return;
}

int main ()
{
  struct nodoRBTree *z, *q;
  int n, m, k, v, i, max, aux;
  while (scanf("%d %d", &n, &m) != EOF){
    max = 0;
    z = NULL;
    q = NULL;
    int In[100005];
    for (i = 1; i <= n; i++){
      scanf("%d", &k);
      In[i] = k;
      if (k > max)
        max = k;
    }
    int Hz[max+5];
    struct nodoRBTree *Elm[max+5];
    for (i = 0; i <= max+4; i++){
      Hz[i] = 0;
      Elm[i] = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
      Elm[i] = Asg_NIL ();
    }
    for (i = 1; i <= n; i++){
      v = In[i];
      aux = Hz[v];
      aux++;
      Hz[v] = aux;
      z = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
      z->key = Hz[v];
      z->posn = i;
      z->color = Rojo;
      z->left = Asg_NIL();
      (z->left)->p = z;
      z->right = Asg_NIL();
      (z->right)->p = z;
      z->p = Asg_NIL();
      Elm[v] = RB_insert (Elm[v], z);
    }
    for (i = 1; i <= m; i++){
      scanf("%d %d", &k, &v);
      if (Hz[v] < k)
        printf("0\n");
      if (Hz[v] >= k){
        q = Treesearch (Elm[v], k);
        aux = q->posn;
        printf("%d\n", aux);
      }
    }
    for (i = 0; i <= n; i++){
      if (Hz[i] == 0){
        free (Elm[i]);
      }
      if (Hz[i] >= 1){
        freeTree (Elm[i], Hz[i]);
      }
      Elm[i] = NULL;
    }
  }
  return 0;
}
