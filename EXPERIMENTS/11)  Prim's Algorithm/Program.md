## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print(int n, int arr[])
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_Matrix(int n, int arr[], int matrix[][20])
{
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void input(int n, int arr[])
{
    int ele, i, j, first;
    printf("Enter : ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ele);
        arr[i] = ele;
    }
    return;
}

void link(int n, int arr[], int matrix[][20])
{
    int loop;
    int a, b, a_index, b_index, weight;
    printf("\nTotal no. of edges : ");
    scanf("%d", &loop);
    for (int k = 0; k < loop; k++)
    {
        printf("Link betw : ");
        scanf("%d %d", &a, &b);
        printf("Weight = ");
        scanf("%d", &weight);
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == a)
            {
                a_index = i;
            }
            if (arr[i] == b)
            {
                b_index = i;
            }
        }
        matrix[a_index][b_index] = weight;
        matrix[b_index][a_index] = weight;
    }
}

void prim(int n, int arr[], int matrix[][20], int result[])
{
    int result_index = 0;
    int visited[n], count = 0, end, start, min;
    visited[0] = 0;
    while (count < n - 1)
    {
        min = INT_MAX;
        for (int i = 0; i <= count; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[visited[i]][j] != 0 && matrix[visited[i]][j] < min)
                {
                    start = visited[i];
                    end = j;
                    min = matrix[start][end];
                }
            }
        }
        result[result_index] = arr[start];
        result_index++;
        result[result_index] = arr[end];
        result_index++;
        result[result_index] = matrix[start][end];
        result_index++;
        for (int i = 0; i < n; i++)
        {
            matrix[i][end] = 0;
        }
        matrix[end][start] = 0;
        count++;
        visited[count] = end;
    }
}

int main()
{
    int n;
    printf("Total no. of elements : ");
    scanf("%d", &n);
    int arr[n];
    input(n, arr);
    int matrix[n][20], result[3 * (n - 1)];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }
    link(n, arr, matrix);
    printf("\nThe Adjacency matrix is:\n");
    print_Matrix(n, arr, matrix);
    prim(n, arr, matrix, result);
    printf("\nMinimum Spanning Tree (MST) : \n");
    int cost = 0;
    for (int i = 0; i < 3 * (n - 1); i += 3)
    {
        printf("%d -- %d == %d\n", result[i], result[i + 1], result[i + 2]);
        cost += result[i + 2];
    }
    printf("\nTotal cost of MST : %d\n", cost);
    return 0;
}
```
## Output:
```
Total no. of elements : 6
Enter :  1 2 3 4 5 6

Total no. of edges : 9
Link betw : 1 2
Weight = 6
Link betw : 1 4
Weight = 5
Link betw : 2 3
Weight = 10
Link betw : 2 4
Weight = 1
Link betw : 2 5
Weight = 3
Link betw : 3 5
Weight = 7
Link betw : 3 6
Weight = 9
Link betw : 4 5
Weight = 5
Link betw : 5 6
Weight = 2

The Adjacency matrix is:
 1 2 3 4 5 6 
1 0 6 0 5 0 0 
2 6 0 10 1 3 0 
3 0 10 0 0 7 9 
4 5 1 0 0 5 0 
5 0 3 7 5 0 2 
6 0 0 9 0 2 0 

Minimum Spanning Tree (MST) : 
1 -- 4 == 5
4 -- 2 == 1
2 -- 5 == 3
5 -- 6 == 2
2 -- 1 == 6

Total cost of MST : 17
```
