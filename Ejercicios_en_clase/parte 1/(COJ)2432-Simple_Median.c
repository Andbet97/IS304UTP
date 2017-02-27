#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define infinite 2147483647
#define MAX 100005

long int A[MAX];

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
	int n, i;
	double result;
	while (1==1){
		scanf ("%d", &n);
		if (n == 0)
			break;
		for (i=1; i<=n; i++)
			scanf ("%ld", &A[i]);
		MergeSort (A, 1, n);
		if (n%2 == 1){
			printf ("%.1lf\n", (double)A[(n+1)/2]);
		}
		else{
			result = (double)(A[n/2]+A[(n/2)+1]);
			result /= 2;
			printf ("%.1lf\n", result); 
		}
	}
	return 0;
}
