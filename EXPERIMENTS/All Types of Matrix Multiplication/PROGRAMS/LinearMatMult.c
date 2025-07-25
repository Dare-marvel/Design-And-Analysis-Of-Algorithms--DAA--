// This code is written by Adwait Purao
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

void print_mat(int rows, int cols, int **X)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", *(*(X + i) + j));
        }
        printf("\n");
    }
}

void print_mat_range(int k, int sizes[10][2], int ***arr_of_mat)
{
    printf("M%d (%d x %d)\n", k, sizes[k - 1][0], sizes[k - 1][1]);
    print_mat(sizes[k - 1][0], sizes[k - 1][1], arr_of_mat[k - 1]);
}

int **add(int **A, int **B, int **C, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

int **subtract(int **A, int **B, int **C, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void Init(int **mat, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mat[i][j] = 0;
        }
    }
}

int **mat_mult(int **result, int **A, int **B, int n, int m, int p)
{
    int sum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            sum = 0;
            for (int k = 0; k < m; k++)
            {
                sum += (*(*(A + i) + k)) * (*(*(B + k) + j));
            }
            *(*(result + i) + j) = sum;
        }
    }
    return result;
}


int main()
{
    srand(time(NULL));

    int min = 1, max = 48, numb;
    int randomNum[11];
    for (int i = 0; i < 11; i++)
    {
        numb = (rand() % (max - min + 1)) + min;
        randomNum[i] = numb;
    }
    int sizes[10][2];
    for (int i = 0; i < 10; i++)
    {
        sizes[i][0] = randomNum[i];
        sizes[i][1] = randomNum[i + 1];
    }
    printf("Sizes\n");
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
            printf("%d ", sizes[i][j]);
        printf("\n");
    }
    int ***arr_of_mat;
    arr_of_mat = (int ***)malloc(10 * sizeof(int **));
    for (int i = 0; i < 48; i++)
    {
        arr_of_mat[i] = (int **)malloc(48 * sizeof(int *));
        for (int j = 0; j < 48; j++)
        {
            arr_of_mat[i][j] = (int *)malloc(48 * sizeof(int));
            // Initialize arr_of_mat[i][j] here
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            for (int k = 0; k < 48; k++)
            {
                *(*(*(arr_of_mat + i) + j) + k) = 0;
            }
        }
    }

    int num;
    for (int i = 0; i < 10; i++)
    {
        int m = sizes[i][0];
        int n = sizes[i][1];

        // generate a matrix of random integers
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                num = rand() % 2;
                *(*(*(arr_of_mat + i) + j) + k) = num;
            }
        }
    }
    
    
    printf("\n Matrices:\n");
    for (int i = 1; i < 11; i++)
    {
        print_mat_range(i, sizes, arr_of_mat);
    }
    
    int **result2 = (int **)malloc(48 * sizeof(int *));
    int **prevRes = (int **)malloc(48 * sizeof(int *));
    for (int i = 0; i < 48; i++)
    {
        result2[i] = (int *)malloc(sizeof(int) * 48);
        prevRes[i] = (int *)malloc(sizeof(int) * 48);
    }
    
    int ** pre1 = arr_of_mat[0];
    int ** pre2 = arr_of_mat[1];
    printf("pre1\n");
    print_mat(sizes[0][0],sizes[0][1],pre1);
    printf("pre2\n");
    print_mat(sizes[1][0],sizes[1][1],pre2);
    
    Init(prevRes, sizes[0][0],sizes[1][1]);
    
    // printf("\n\ncheck1\n");
    clock_t sttime2 = clock();
    mat_mult(result2,pre1,pre2,48,48,48);
    // printf("\nprevRes: (%d x %d)\n", sizes[0][0], sizes[1][1]);
    // print_mat(sizes[0][0],sizes[1][1],prevRes);
    
    for (int i = 1; i < 9; i++)
    {
        int **matrix1 = arr_of_mat[i+1];
        Init(result2,48,48);
        mat_mult(result2,pre1,pre2,48,48,48);
        Init(prevRes,48,48);
        for (int j = 0; j < 48; j++)
        {
            for (int k = 0; k < 48; k++)
            {
                prevRes[j][k] = result2[j][k];
            }
        }
        // printf("\n\nResult at step : %d\n\n",i+1);
        // print_mat(sizes[0][0],sizes[i+1][1],result2);
    }
    double time2 = (double)(clock() - sttime2) / CLOCKS_PER_SEC;

    printf("\nResultant Matrix (from method 1 - Linear Matrix Multiplication): (%d x %d)\n", sizes[0][0], sizes[9][1]);
    print_mat(sizes[0][0], sizes[9][1], result2);
    
    // Free the memory allocated for the matrices
    for (int i = 0; i < 48; i++)
    {
        free(result2[i]);
        free(prevRes[i]);
    }
    free(result2);
    free(prevRes);
    return 0;   
}
