#include <stdio.h>
#include <stdlib.h>

int BinarySearch (long int A[], int i, int j, long int n)
{
  int m, result=-1;
  while (i<=j){
    m=(i+j)>>1; /*m=(i+j)/2*/
    if (A[m]==n){
      result = m;
      break;
    }
    else{
      if (n>A[m])
        i=m+1;
      else
        j=m-1;
    }
  }
  if (result == -1)
    result = (-1*i)-1;
  return result;
}

int main ()
{
  long int A[50005];
  long int K[25005];
  int n, q, i, posn;
  long int k;
  scanf("%d", &n );
  for (i=1; i<=n; i++)
    scanf ("%ld", &A[i]);
  scanf ("%d", &q);
  for (i=1; i<=q; i++)
    scanf ("%ld", &K[i]);
  for (i=1; i<=q; i++){
    posn = BinarySearch(A, 1, n, K[i]);
    if (posn < 0)
      posn = ((posn+1)*-1);
    if (posn > n){
      printf("%ld %c\n", A[n], 88);
    }
    if (posn == 1){
    	if (A[posn]==K[i]){
        printf("%c %ld\n", 88, A[posn+1]);
      }
    	else{
        printf("%c %ld\n", 88, A[posn]);
      }
		}
    if (posn == n){
      if (A[n]>K[i]){
        printf("%ld %ld\n", A[n-1], A[n]);
      }
      else{
        printf ("%ld %c\n", A[n-1], 88);
      }
    }
    if ((posn > 1)&&(posn < n)){
      if (A[posn]==K[i]){
        while (A[posn]==K[i]){
          posn--;
        }
        if (posn == 1){
        	if (A[posn]==K[i]){
            printf("%c ", 88);
          }
        	else{
            printf("%ld ", A[posn]);
          }
    		}
        if (posn == 0){
          printf("%c ", 88);
        }
        if (posn > 1){
          printf("%ld ", A[posn]);
        }
        posn++;
        while (A[posn]==K[i]){
          posn++;
        }
        if (posn == n){
          if (A[n]>K[i]){
            printf("%ld\n", A[n]);
          }
          else{
            printf ("%c\n", 88);
          }
        }
        if (posn > n){
          printf("%c\n", 88);
        }
        if (posn < n){
          printf("%ld\n", A[posn]);
        }
      }
      else{
        printf("%ld %d\n", A[posn-1], A[posn]);
      }
    }
  }
  return 0;
}
