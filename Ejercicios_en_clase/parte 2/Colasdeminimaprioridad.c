#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int Heapsize=0;
#define infinito 2147483647

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

void minheapify (int *A,int i)
{
  int l, r, least, aux;
  l = left (i);
  r = right (i);
  if ((l <= Heapsize)&&(A[l] < A[i]))
    least = l;
  else
    least = i;
  if ((r <= Heapsize)&&(A[r] < A[least]))
    least = r;
  if (least != i){
    aux = A[i];
    A[i] = A[least];
    A[least] = aux;
    minheapify (A, least);
  }
  return;
}

int minPQ_minimum (int *A)
{
  return (A[1]);
}

int minPQ_Extract (int *A)
{
  int min;
  if (Heapsize < 1){
    printf("Error\n");
    return 0;
  }
  else {
    min = minPQ_minimum (A);
    A[1] = A[Heapsize];
    Heapsize = Heapsize-1;
    minheapify (A, 1);
    return min;
  }
}

void minPQ_Decreasekey (int *A, int i, int key)
{
  int aux;
  if (key > A[i]){
    printf("Error\n");
    return;
  }
  else {
    A[i] = key;
    while ((i > 1)&&(A[parent (i)] > A[i])){
      aux = A[i];
      A[i] = A[parent (i)];
      A[parent (i)] = aux;
      i = parent (i);
    }
  }
  return;
}

void minPQ_Insert (int *A, int key)
{
  Heapsize = Heapsize+1;
  A[Heapsize] = infinito;
  minPQ_Decreasekey (A, Heapsize, key);
  return;
}

void mostrar (int *A)
{
  int i;
  for (i = 1; i <= Heapsize; i++){
    printf("%d ", A[i]);
  }
  printf("\n");
  return;
}

void menu ()
{
  printf("Colas de minima prioridad\n");
  printf("1.Insertar.\n");
  printf("2.Minimo.\n");
  printf("3.Extraer.\n");
  printf("4.DecreaseKey.\n");
  printf("5.Padre de i.\n");
  printf("6.Left de i.\n");
  printf("7.Right de i.\n");
  printf("8.Mostrar.\n");
  printf("0.Salir.\n");
  return;
}

int main ()
{
  int A[100]; /*solo para la implementacion*/
  int opc=-1, x, n, aux, i;
  while (opc != 0){
    system ("cls");
    menu ();
    printf("Escoja una opcion: \n");
    scanf("%d", &opc);
    switch (opc){
      case 1:{
        system ("cls");
        printf("Cuantos elementos desea insertar: \n");
        scanf("%d", &x);
        for (i = 1; i <= x; i++){
          printf("Elemento %d: ", i);
          scanf("%d", &n);
          minPQ_Insert (A, n);
          mostrar (A);
        }
        getch ();
        break;
      }
      case 2:{
        system ("cls");
        printf("El minimo es: %d\n", minPQ_minimum (A));
        getch ();
        break;
      }
      case 3:{
        system ("cls");
        printf("Cuantos elementos desea Extraer: \n");
        scanf("%d", &x);
        for (i = 1; i <= x; i++){
          aux = minPQ_Extract (A);
          printf("Elemento eliminado: %d\n", aux);
          mostrar (A);
        }
        getch ();
        break;
      }
      case 4:{
        system ("cls");
        printf("Cuantos veces desea hacer Decreasekey: \n");
        scanf("%d", &x);
        for (i = 1; i <= x; i++){
          printf("%d. Posicion i: ", i);
          scanf("%d", &n);
          printf("Key: ");
          scanf("%d", &aux);
          minPQ_Decreasekey (A, n, aux);
          mostrar (A);
        }
        getch ();
        break;
      }
      case 5:{
        system ("cls");
        printf("De quien desea saber el padre: \n");
        scanf ("%d", &x);
        printf("El padre de %d es %d.\n", x, parent (x));
        getch ();
        break;
      }
      case 6:{
        system ("cls");
        printf("De quien desea saber el hijo, o posible hijo, por la izquierda: \n");
        scanf ("%d", &x);
        printf("El padre de %d es %d.\n", x, left (x));
        getch ();
        break;
      }
      case 7:{
        system ("cls");
        printf("De quien desea saber el hijo, o posible hijo, por la derecha: \n");
        scanf ("%d", &x);
        printf("El padre de %d es %d.\n", x, right (x));
        getch ();
        break;
      }
      case 8:{
        system ("cls");
        mostrar (A);
        getch ();
        break;
      }
      case 0:{
        break;
      }
    }
  }
  return 0;
}
