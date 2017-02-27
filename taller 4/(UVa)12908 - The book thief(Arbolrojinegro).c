#include <stdio.h>
#include <stdlib.h>

#define NIL -2147483647
#define Negro 78
#define Rojo 82

struct nodoRBTree{
  int posn;
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
  x->key = NIL;
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
  else
    y = Asg_NIL ();
  x = T;
  while (x->key != NIL) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->p = y;
  if (y->key == NIL)
    T = z;
  else{
    if (z->key < y->key)
      y->left = z;
    else
      y->right = z;
  }
  return RB_insert_fixup (T, z);
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

struct nodoRBTree *Treemax (struct nodoRBTree *T)
{
	struct nodoRBTree *x;
	x = T;
	while ((x->right)->key != NIL){
		x = x->right;
	}
	return x;
}

struct nodoRBTree *crear ()
{
  struct nodoRBTree *T, *z;
  T = Asg_NIL ();
  int i, cont = 0;
  for (i = 1; cont<=100000000; i++){
    cont += i;
    z = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
    z->color = Rojo;
    z->left = Asg_NIL();
    (z->left)->p = z;
    z->right = Asg_NIL();
    (z->right)->p = z;
    z->p = Asg_NIL();
    z->key = cont;
    z->posn = i;
    T = RB_insert (T, z);
  }
  return T;
}

int main ()
{
  struct nodoRBTree *T, *z, *z1;
  T = crear ();
  int n;
  while (1 == 1){
    scanf ("%d", &n);
    if (n == 0)
      break;
    if (n == 100000000){
      z1 = Treemax (T);
      printf("%d %d\n", (z1->key)-n, z1->posn);
    }
    if (n != 100000000) {
      z = Treesearch (T, n);
      if (z->key == n){
        z1 = sucessor (z);
        printf("%d %d\n", (z1->key)-n, z1->posn);
      }
      if (z->key == NIL){
        if (z == (z->p)->right){
          z1 = sucessor (z->p);
          printf("%d %d\n", (z1->key)-n, z1->posn);
        }
        else {
          z1 = z->p;
          printf("%d %d\n", (z1->key)-n, z1->posn);
        }
      }
    }
  }
  return 0;
}
