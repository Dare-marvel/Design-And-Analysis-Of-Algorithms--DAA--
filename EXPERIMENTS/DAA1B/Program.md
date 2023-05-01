### [Insertion Sort](https://www.geeksforgeeks.org/insertion-sort/)
### [Selection Sort](https://www.geeksforgeeks.org/selection-sort/)
### [Comparison](https://www.geeksforgeeks.org/difference-between-insertion-sort-and-selection-sort/)

## Explanation of the Code:
* `The program begins with the inclusion of necessary header files:`<br>stdio.h, stdlib.h, and time.h. The Init function initializes an array to all zeros. The swap function takes two pointers as arguments and swaps their values.
* `The program defines two sorting functions:` InsertionSort and SelectionSort. The InsertionSort function implements the insertion sort algorithm on the input array. It starts with the second element of the array and iteratively inserts the next element into the sorted sub-array by comparing it with the previous elements in the sorted sub-array. The function returns the elapsed time for sorting.
* The SelectionSort function implements the selection sort algorithm on the input array. It iteratively finds the minimum element in the unsorted sub-array and places it at the beginning of the unsorted sub-array. The function returns the elapsed time for sorting.
* The main function begins by initializing the random number generator using the srand function with the current time as the seed. It then creates a file named "randomnum.txt" and generates 100000 random numbers between 100000 and 1000000 using the rand function and writes them to the file.
* The program then initializes an upper limit for the array size and prints the header for the result table. It then runs a loop 1000 times, each time increasing the array size by 100. For each iteration, the program reads the numbers from the file, copies them to two arrays, one for each sorting algorithm. It then sorts the arrays using the two sorting functions and prints the iteration count, elapsed time for Insertion Sort, and elapsed time for Selection Sort.
* Finally, the program returns 0 to indicate successful completion of the main function.
* In summary, this program generates a file with random numbers and measures the elapsed time for sorting them using Insertion Sort and Selection Sort algorithms. It then prints the result in a table. This program can be used to compare the performance of these two sorting algorithms on different data sizes.


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
