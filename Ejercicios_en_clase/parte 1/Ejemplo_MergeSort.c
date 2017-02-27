#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define infinite 2147483647

void merge (int A[], int p, int q, int r)
{
  int n1=q-p+1, n2=r-q, i, j, k;
  int L[n1+2], R[n2+2];
  for (i=1; i<=n1; i++)
    L[i]=A[p+i-1];
  for (j=1; j<=n2; j++)
    R[j]=A[q+j];
  L[n1+1]=infinite;
  R[n2+1]=infinite;
  i=1;
  j=1;
  for (k=p; k<=r; k++){
    if (L[i]<=R[j]){
      A[k]=L[i];
      i++;
    }
    else{
      A[k]=R[j];
      j++;
    }
  }
  return;
}

void MergeSort (int A[], int p, int r)
{
  if (p<r){
    int q; 
	q=(p+r)>>1;
    MergeSort (A, p, q);
    MergeSort (A, q+1, r);
    merge (A, p, q, r);
  }
  return;
}

int main ()
{
  int A[1001], n, i, j;
  while (scanf ("%d", &n) != EOF){
    for (i=1; i<=n; i++)
      scanf ("%d", &A[i]);
    MergeSort (A, 1, n);
    for (i=1; i<=n; i++)
      printf ("%d ", A[i]);
    printf ("\n");
  }
  return 0;
}
