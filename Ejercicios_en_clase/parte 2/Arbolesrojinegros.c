#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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

void inordertree (struct nodoRBTree *T, int count)
{
	int aux;
	struct nodoRBTree *x;
	x = T;
	if (x->key != NIL){
		count++;
		aux = count;
		inordertree (x->right, count);
		while (aux-1 != 0){
			printf("         ");
			aux--;
		}
		printf ("%d%c", x->key, x->color);
		printf("\n");
		inordertree (x->left, count);
	}
  else{
		aux = count;
		while (aux != 0){
			printf("         ");
			aux--;
		}
		printf("NIL\n");
	}
	return;
}

void inordertreeiterativo (struct nodoRBTree *T)
{
  struct nodoRBTree *C, *P;
  if (T->key == NIL)
    return ;
  C = T;
  while (C->key != NIL){
    if ((C->right)->key == NIL){
      printf("%d\n", C->key);
      C = C->left;
    }
    else {
      P = C->right;
      while ((P->left)->key != NIL && P->left != C)
        P = P->left;
      if ((P->left)->key == NIL) {
        free (P->left);
        P->left = C;
        C = C->right;
      }
      else {
        P->left = Asg_NIL ();
        printf("%d\n", C->key);
        C = C->left;
      }
    }
  }
  return;
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

struct nodoRBTree *predecessor (struct nodoRBTree *x)
{
	struct nodoRBTree *y;
	if ((x->left)->key != NIL){
		return Treemax (x->left);
	}
	y = x->p;
	while ((y->key != NIL)&&(x == y->left)) {
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

/********************************************************************/

void menu ()
{
	printf(" Arboles de busqueda binaria.\n");
	printf("1. Agregar elementos al arbol.\n");
	printf("2. Buscar elementos en el arbol.\n");
	printf("3. Minimo del arbol.\n");
	printf("4. Maximo del arbol.\n");
	printf("5. Sucesor.\n");
	printf("6. Predecesor.\n");
	printf("7. Borrar del arbol.\n");
	printf("8. Mostrar el arbol.\n");
	printf("0. Salir.\n");
	return;
}

/********************************************************************/

int main ()
{
	struct nodoRBTree *T, *z, *z1;
	T = Asg_NIL ();
	int n, elemento, i;
	int option = -1;
	while (option != 0){
		system ("cls");
		menu ();
		scanf ("%d", &option);
		switch (option) {
			case 1:{
				system ("cls");
				printf ("Cuantos elementos quiere ingrasar al arbol: ");
				scanf ("%d", &n);
				for (i = 1; i<=n; i++){
					printf ("\nElemento %d: ", i);
					scanf ("%d", &elemento);
					printf("\n");
					z = (struct nodoRBTree *)malloc(sizeof(struct nodoRBTree));
					z->key = elemento;
          z->color = Rojo;
					z->left = Asg_NIL();
          (z->left)->p = z;
					z->right = Asg_NIL();
          (z->right)->p = z;
					z->p = Asg_NIL();
					T = RB_insert (T, z);
					inordertree (T, 0);
          inordertreeiterativo (T);
					printf ("\n");
				}
				getch ();
				break;
			}
			case 2:{
				system ("cls");
				if (T->key == NIL){
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
				printf ("\nCuantos elementos desea buscar en el arbol: ");
				scanf ("%d", &n);
				for (i = 1; i<=n; i++){
					printf ("\nBusqueda %d: ", i);
					scanf ("%d", &elemento);
					z = Treesearch (T, elemento);
					if (z->key == NIL)
						printf ("El elemento no esta en el arbol\n");
					else
						printf ("El elemento si esta en el arbol\n");
				}
				getch ();
				break;
			}
			case 3:{
				system ("cls");
				if (T->key == NIL){
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
				z = Treemin (T);
				printf("El minimo de este arbol es: %d\n", z->key);
				getch ();
				break;
			}
			case 4:{
				system ("cls");
				if (T->key == NIL){
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
				z = Treemax (T);
				printf("El maximo de este arbol es: %d\n", z->key);
				getch ();
				break;
			}
			case 5:{
				system ("cls");
				if (T->key == NIL){
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
				printf("De que elemento dese saber el sucesor: ");
				scanf ("%d", &elemento);
				z = Treesearch (T, elemento);
				i = z->key;
				z1 = sucessor (z);
				printf("El Sucesor de %d es: %d\n", i, z1->key);
				getch ();
				break;
			}
			case 6:{
				system ("cls");
				if (T->key == NIL){
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
				printf("De que elemento dese saber el Predecesor: ");
				scanf ("%d", &elemento);
				z = Treesearch (T, elemento);
				i = z->key;
				z1 = predecessor (z);
				printf("El Predecesor de %d es: %d\n", i, z1->key);
				getch ();
				break;
			}
			case 7:{
				system ("cls");
				if (T->key != NIL){
					inordertree (T, 0);
					printf("\nQue elemento desea borrar: \n");
					scanf("%d", &elemento);
					z = Treesearch (T, elemento);
					if (z->key == NIL){
						printf("El elemento no esta en el arbol.\n");
						getch ();
						break;
					}
					T = RB_delete (T, z);
					system ("cls");
					inordertree (T, 0);
					getch ();
					break;
				}
				else{
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
			}
			case 8:{
				system ("cls");
				if (T->key == NIL){
					printf("El arbol esta vacio.\n");
				}
				else {
					inordertree (T, 0);
				}
				getch ();
				break;
			}
			case 0:
				break;
		}
	}
	return 0;
}
