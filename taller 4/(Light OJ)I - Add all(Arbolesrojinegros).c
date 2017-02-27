#include <stdio.h>
#include <stdlib.h>

#define NIL -2147483647
#define Negro 78
#define Rojo 82

struct nodoRBTree{
  int key;
  char color;
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
  x->key = NIL;
  return x;
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

int main ()
{
  struct nodoRBTree *T, *z, *m, *s;
  int n, i, elemento, aux;
	while (1 == 1){
		scanf("%d", &n);
		if (n == 0)
			break;
    T = Asg_NIL ();
	  for (i = 1; i<=n; i++){
	    scanf("%d", &elemento);
	    z = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
      z->key = elemento;
      z->color = Rojo;
      z->left = Asg_NIL();
      (z->left)->p = z;
      z->right = Asg_NIL();
      (z->right)->p = z;
      z->p = Asg_NIL ();
	    T = RB_insert (T, z);
	  }
    elemento = 0;
	  for (i = 1; i<n; i++){
      m = Treemin (T);
      s = sucessor (m);
      aux = (m->key)+(s->key);
      elemento += aux;
      T = RB_delete (T,m);
      T = RB_delete (T,s);
      z = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
      z->key = aux;
      z->color = Rojo;
      z->left = Asg_NIL ();
      (z->left)->p = z;
      z->right = Asg_NIL ();
      (z->right)->p = z;
      z->p = NULL;
      T = RB_insert (T, z);
    }
	  printf("%d\n", elemento);
    free (T->left);
    free (T->right);
    free (T->p);
    free (T);
	}
  return 0;
}
