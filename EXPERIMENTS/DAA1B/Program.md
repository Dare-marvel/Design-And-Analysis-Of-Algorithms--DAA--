### [Insertion Sort](https://www.geeksforgeeks.org/insertion-sort/)
### [Selection Sort](https://www.geeksforgeeks.org/selection-sort/)
### [Comparison](https://www.geeksforgeeks.org/difference-between-insertion-sort-and-selection-sort/)

## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Init(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=0;
    }
}
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

double InsertionSort(int arr[], int n)
{
    clock_t t;
    t = clock();
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j]>key)
        {
            arr[j + 1] = arr[j];
            j=j-1;
        }
        arr[j + 1] = key;
    }
    t = clock() - t;
    double elapsed_time = ((double)t) / CLOCKS_PER_SEC;
    return elapsed_time;
}

double SelectionSort(int arr[], int n)
{
    clock_t t;
    t = clock();
    int min,i,j;
    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (min != i)
            {
                swap(&arr[min], &arr[i]);
            }
    }
    t = clock() - t;
    double elapsed_time = ((double)t) / CLOCKS_PER_SEC;
    return elapsed_time;
}
int main()
{
    srand(time(0));
    FILE *fp;
    fp = fopen("randomnum.txt", "w");
    for (int i = 0; i < 100000; i++)
    {
        fprintf(fp, "%d\n", rand() % 900001 + 100000);
    }
    int upper_limit = 100;
    fclose(fp);
    printf("ItCount\t InsSort\t SelSort\n");
    for (int i = 0; i < 1000; i++)
    {
        fp = fopen("randomnum.txt","r");
        int arr1[upper_limit],arr2[upper_limit],temp_num;
        for (int j = 0; j < upper_limit; j++)
        {
            fscanf(fp,"%d", &temp_num);
            arr1[j]=temp_num;
            arr2[j]=temp_num;
        }
        fclose(fp);
        printf("%d\t%lf\t%lf\n", (i + 1), InsertionSort(arr1, upper_limit), SelectionSort(arr2, upper_limit));
        fflush(stdout);
        upper_limit += 100;
    }
    return 0;
}
```
