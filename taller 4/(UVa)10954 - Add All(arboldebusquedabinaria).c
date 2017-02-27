#include <stdio.h>
#include <stdlib.h>

struct nodoTree{
	int key;
	struct nodoTree *left;
	struct nodoTree *right;
	struct nodoTree *p;
};

struct nodoTree *Treemin (struct nodoTree *T)
{
	struct nodoTree *x;
	x = T;
	while (x->left != NULL){
		x = x->left;
	}
	return x;
}

struct nodoTree *TreeInsert (struct nodoTree *T, struct nodoTree *z)
{
	struct nodoTree *x, *y;
	y = NULL;
	x = T;
	while (x != NULL){
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == NULL)
		T = z;
	else{
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	}
	return T;
}

struct nodoTree *sucessor (struct nodoTree *x)
{
	struct nodoTree *y;
	if (x->right != NULL){
		return Treemin (x->right);
	}
	y = x->p;
	while ((y != NULL)&&(x == y->right)) {
		x = y;
		y = y->p;
	}
	return y;
}

struct nodoTree *Treedelete (struct nodoTree *T, struct nodoTree *z)
{
	struct nodoTree *x, *y;
	if ((z->left == NULL)||(z->right == NULL))
		y = z;
	else
		y = sucessor (z);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->p = y->p;
	if (y->p == NULL)
		T = x;
	else {
		if (y == (y->p)->left)
			(y->p)->left = x;
		else
			(y->p)->right = x;
	}
	if (y != z)
		z->key = y->key;
	free (y);
	return T;
}

int main ()
{
  struct nodoTree *T, *z, *m, *s;
  int n, i, elemento, aux;
	while (1 == 1){
		scanf("%d", &n);
		if (n == 0)
			break;
		T = NULL;
	  for (i = 1; i<=n; i++){
	    scanf("%d", &elemento);
	    z = (struct nodoTree *)malloc(sizeof(struct nodoTree));
	    z->key = elemento;
	    z->left = NULL;
	    z->right = NULL;
	    z->p = NULL;
	    T = TreeInsert (T, z);
	  }
		elemento = 0;
		for(i = 1 ; i<n; i++){
			m = Treemin (T);
			s = sucessor (m);
			aux = (m->key)+(s->key);
			elemento += aux;
			T = Treedelete (T, m);
			T = Treedelete (T, s);
			z = (struct nodoTree *)malloc(sizeof(struct nodoTree));
			z->key = aux;
			z->left = NULL;
	    z->right = NULL;
	    z->p = NULL;
			T = TreeInsert (T, z);
		}
	  printf("%d\n", elemento);
		free (T);
	}
  return 0;
}
