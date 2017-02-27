#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    char palabra[100];
} dicc;

dicc A[120005];


int BinarySearch(dicc A[], int i, int j, char pal[100])
{
    int m;

    if(i > j)
        return -1;
    else
    {
        m = (i + j)/2;
        if(strcmp(A[m].palabra, pal) == 0)
            return m;
        else
        {
            if(strcmp(A[m].palabra, pal) < 0)
                BinarySearch(A, m + 1, j, pal);
            else
                BinarySearch(A, i, m - 1, pal);
        }
    }
}


int main()
{
    char pal[100], izquierdapal[200], derechapal[200];
    int m, n, len, i, j, l, k;

    m = 0;

    while(scanf("%s", pal) != EOF)
    {
        m++;
        strcpy(A[m].palabra, pal);
    }

    n = m;

    for(i=1; i<=n; i++)
    {
        strcpy(pal, A[i].palabra);

        len = strlen(pal);
        for(k=1; k<len; k++)
        {
            for(j=0; j<k; j++)
            {
                izquierdapal[j] = pal[j];
            }
            izquierdapal[j] = '\0';

            l=0;
            for(j=k; j<len; j++)
            {
                derechapal[l] = pal[j];
                l++;
            }
            derechapal[l] = '\0';

            if((BinarySearch(A, 1, n, izquierdapal) > 0) &&
               (BinarySearch(A, 1, n, derechapal) > 0))
            {
                printf("%s\n", pal);
                break;
            }
        }
    }
    return 0;
}
