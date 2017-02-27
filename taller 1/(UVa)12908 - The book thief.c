#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){
  long int n, pag, r;
  while (1==1){
  	scanf ("%ld", &n);
  	if (n==0)
  		break;
  	pag = (sqrt (8*n +1) -1)/2;
  	pag++;
  	r = pag*(pag++)>>1;
  	printf ("%ld %ld\n", r-n, pag-1);
  }
  return 0;
}
