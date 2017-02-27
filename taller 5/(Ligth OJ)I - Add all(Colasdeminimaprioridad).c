#include <stdio.h>
#include <stdlib.h>

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
    printf("Error : %d\n", Heapsize);
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

int main ()
{
  int n, i, r;
  while (1 == 1){
    scanf("%d", &n);
    if (n == 0)
      break;
    Heapsize = 0;
    int A[n+5];
    for (i = 1; i<= n; i++){
      scanf("%d", &r);
      minPQ_Insert (A, r);
    }
    r = 0;
    while (1 == 1){
      i = 0;
      if (Heapsize == 0)
        break;
      i += minPQ_Extract (A);
      i += minPQ_Extract (A);
      r += i;
      if (Heapsize > 0)
        minPQ_Insert (A, i);
    }
    printf("%d\n", r);
  }
  return 0;
}
