#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define infinite 2147483647

int A[1000005];
int L[500005], R[500005];

void Merge(int A[], int p, int q, int r)
{
    int n1 = q - p + 1, n2 = r - q, i, j, k;

    for(i=1; i<=n1; i++)
        L[i] = A[p + i - 1];

    for(j=1; j<=n2; j++)
        R[j] = A[q + j];

    L[n1 + 1] = infinite;
    R[n2 + 1] = infinite;

    i = 1;
    j = 1;

    for(k=p; k<=r; k++)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
    return;
}

void MergeSort(int A[], int p, int r)
{
    int q;

    if(p < r)
    {
        q = (p + r)/2;
        MergeSort(A, p, q);
        MergeSort(A, q+1, r);
        Merge(A, p, q, r);
    }
    return;
}

int BinarySearch(int A[], int i, int j, int n)
{
    int m;

    if(i > j)
        return -1;
    else
    {
        m = (i + j)/2;
        if(A[m] == n)
            return m;
        else
        {
            if(n > A[m])
                BinarySearch(A, m + 1, j, n);
            else
                BinarySearch(A, i, m - 1, n);
        }
    }
}


int main()
{
    int x, n, i, lego1, lego2, m, aux;

    while(scanf("%d", &x) != EOF)
    {
        x *= 10000000;

        scanf("%d", &n);

        for(i=1; i<=n; i++)
            scanf("%d", &A[i]);

        MergeSort(A, 1, n);

        aux = 0;
        for(i=1; i<=n; i++)
        {
            lego1 = A[i];
            lego2 = x - lego1;
            m = BinarySearch(A, i + 1, n, lego2);
            if(m != -1)
            {
                printf("yes %d %d\n", lego1, lego2);
                aux = 1;
                break;
            }
        }

        if(aux == 0)
            printf("danger\n");
    }

    return 0;
}
