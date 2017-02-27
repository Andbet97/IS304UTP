#include <stdio.h>
#include <stdlib.h>

int BynarySearch (int A[], int i, int j, int n)
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

int main(){
  int W[100005], k;
  int n, q, i, posn;
  while (scanf ("%d %d\n", &n, &q) != EOF){
    scanf ("%d", &W[1]);
    W[1] = 1;
    for (i=2; i<=n; i++)
  		scanf ("%d", &W[i]);
    for (i=2; i<=n; i++)
  		W[i] += W[i-1];
    for (i=1; i<=q; i++){
        scanf ("%d", &k);
        posn = BynarySearch (W, 1, n, k);
        if (posn<0)
            posn = ((posn+2)*-1);
        printf("%d ", posn);
    }
    printf ("\n");
  }
  return 0;
}
