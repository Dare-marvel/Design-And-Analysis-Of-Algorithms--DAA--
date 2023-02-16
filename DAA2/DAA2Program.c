#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int a[], int start, int end)
{
    int pivot = a[end];
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[end];
    a[end] = t;
    return (i + 1);
}

double quick(int a[], int start, int end)
{
    if (start < end)
    {
        int p = partition(a, start, end);
        quick(a, start, p - 1);
        quick(a, p + 1, end);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;

    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    double qust,mest;
    srand(time(0));
    FILE *fp;
    fp = fopen("randomnum.txt", "w");
    for (int i = 0; i < 100000; i++)
    {
        fprintf(fp, "%d\n", rand() % 900001 + 100000);
    }
    int upper_limit = 100;
    fclose(fp);
    printf("ItCount\tMerSort\tQuickSort\n");
    for (int i = 0; i < 1000; i++)
    {
        fp = fopen("randomnum.txt", "r");
        int arr1[upper_limit], arr2[upper_limit], temp_num;
        for (int j = 0; j < upper_limit; j++)
        {
            fscanf(fp, "%d", &temp_num);
            arr1[j] = temp_num;
            arr2[j] = temp_num;
        }
        fclose(fp);

        clock_t t;
        t = clock();
        mergeSort(arr2,0,upper_limit-1);
        t = clock() - t;
        mest = ((double)t) / CLOCKS_PER_SEC;
        clock_t t1;
        t1 = clock();
        qust=quick(arr1,0,upper_limit-1);
        t1 = clock() - t1;
        qust = ((double)t1) / CLOCKS_PER_SEC;
        printf("%lf\t%lf\n", mest, qust);
        fflush(stdout);
        upper_limit += 100;
    }
    return 0;
}