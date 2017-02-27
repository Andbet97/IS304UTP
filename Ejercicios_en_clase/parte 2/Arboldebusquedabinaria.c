#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct nodoTree{
	int key;
	struct nodoTree *left;
	struct nodoTree *right;
	struct nodoTree *p;
};

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

void inordertree (struct nodoTree *T, int count)
{
	int aux;
	struct nodoTree *x;
	x = T;
	if (x != NULL){
		count++;
		aux = count;
		inordertree (x->right, count);
		while ((aux-1) != 0){
			printf("    ");
			aux--;
		}
		printf ("%d", x->key);
		printf("\n");
		inordertree (x->left, count);
	}
	else{
		aux = count;
		while (aux != 0){
			printf("    ");
			aux--;
		}
		printf("-\n");
	}
	return;
}

struct nodoTree *Treesearch (struct nodoTree *x, int k)
{
	while ((x != NULL)&&(k != x->key)){
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

struct nodoTree *Treemax (struct nodoTree *T)
{
	struct nodoTree *x;
	x = T;
	while (x->right != NULL){
		x = x->right;
	}
	return x;
}

struct nodoTree *Treemin (struct nodoTree *T)
{
	struct nodoTree *x;
	x = T;
	while (x->left != NULL){
		x = x->left;
	}
	return x;
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

struct nodoTree *predecessor (struct nodoTree *x)
{
	struct nodoTree *y;
	if (x->left != NULL){
		return Treemax (x->left);
	}
	y = x->p;
	while ((y != NULL)&&(x == y->left)) {
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
	struct nodoTree *T, *z, *z1;
	T = NULL;
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
					z = (struct nodoTree *)malloc(sizeof(struct nodoTree));
					z->key = elemento;
					z->left = NULL;
					z->right = NULL;
					z->p = NULL;
					T = TreeInsert (T, z);
					inordertree (T, 0);
					printf ("\n");
				}
				getch ();
				break;
			}
			case 2:{
				system ("cls");
				if (T == NULL){
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
					if (z == NULL)
						printf ("El elemento no esta en el arbol\n");
					else
						printf ("El elemento si esta en el arbol\n");
				}
				getch ();
				break;
			}
			case 3:{
				system ("cls");
				if (T == NULL){
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
				if (T == NULL){
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
				if (T == NULL){
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
				if (T == NULL){
					printf("El arbol esta vacio.\n");
					getch ();
					break;
				}
				printf("De que elemento dese saber el sucesor: ");
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
				if (T != NULL){
					inordertree (T, 0);
					printf("\nQue elemento desea borrar: \n");
					scanf("%d", &elemento);
					z = Treesearch (T, elemento);
					if (z == NULL){
						printf("El elemento no esta en el arbol.\n");
						getch ();
						break;
					}
					T = Treedelete (T, z);
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
				if (T == NULL){
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
