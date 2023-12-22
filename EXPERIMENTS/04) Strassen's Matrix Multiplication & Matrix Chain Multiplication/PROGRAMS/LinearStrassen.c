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

void StrassenMultiplication(int **A, int **B, int **C, int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int i, j;
    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **P, **Q, **R, **S, **T, **U, **V;
    int **tmp1, **tmp2;

    int mid = n / 2;

    // Allocate memory
    A11 = (int **)malloc(mid * sizeof(int *));
    A12 = (int **)malloc(mid * sizeof(int *));
    A21 = (int **)malloc(mid * sizeof(int *));
    A22 = (int **)malloc(mid * sizeof(int *));

    B11 = (int **)malloc(mid * sizeof(int *));
    B12 = (int **)malloc(mid * sizeof(int *));
    B21 = (int **)malloc(mid * sizeof(int *));
    B22 = (int **)malloc(mid * sizeof(int *));

    C11 = (int **)malloc(mid * sizeof(int *));
    C12 = (int **)malloc(mid * sizeof(int *));
    C21 = (int **)malloc(mid * sizeof(int *));
    C22 = (int **)malloc(mid * sizeof(int *));

    P = (int **)malloc(mid * sizeof(int *));
    Q = (int **)malloc(mid * sizeof(int *));
    R = (int **)malloc(mid * sizeof(int *));
    S = (int **)malloc(mid * sizeof(int *));
    T = (int **)malloc(mid * sizeof(int *));
    U = (int **)malloc(mid * sizeof(int *));
    V = (int **)malloc(mid * sizeof(int *));

    tmp1 = (int **)malloc(mid * sizeof(int *));
    tmp2 = (int **)malloc(mid * sizeof(int *));

    for (i = 0; i < mid; i++)
    {
        A11[i] = (int *)malloc(mid * sizeof(int));
        A12[i] = (int *)malloc(mid * sizeof(int));
        A21[i] = (int *)malloc(mid * sizeof(int));
        A22[i] = (int *)malloc(mid * sizeof(int));

        B11[i] = (int *)malloc(mid * sizeof(int));
        B12[i] = (int *)malloc(mid * sizeof(int));
        B21[i] = (int *)malloc(mid * sizeof(int));
        B22[i] = (int *)malloc(mid * sizeof(int));

        C11[i] = (int *)malloc(mid * sizeof(int));
        C12[i] = (int *)malloc(mid * sizeof(int));
        C21[i] = (int *)malloc(mid * sizeof(int));
        C22[i] = (int *)malloc(mid * sizeof(int));

        P[i] = (int *)malloc(mid * sizeof(int));
        Q[i] = (int *)malloc(mid * sizeof(int));
        R[i] = (int *)malloc(mid * sizeof(int));
        S[i] = (int *)malloc(mid * sizeof(int));
        T[i] = (int *)malloc(mid * sizeof(int));
        U[i] = (int *)malloc(mid * sizeof(int));
        V[i] = (int *)malloc(mid * sizeof(int));

        tmp1[i] = (int *)malloc(mid * sizeof(int));
        tmp2[i] = (int *)malloc(mid * sizeof(int));
    }

    // Split matrices A and B into quadrants
    for (i = 0; i < mid; i++)
    {
        for (j = 0; j < mid; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }
    Init(tmp1, mid, mid);
    Init(tmp2, mid, mid);
    // Compute products P, Q, R, S, T, U, V
    StrassenMultiplication(add(A11, A22, tmp1, mid), add(B11, B22, tmp2, mid), P, mid);
    Init(tmp1, mid, mid);
    Init(tmp2, mid, mid);

    StrassenMultiplication(add(A21, A22, tmp1, mid), B11, Q, mid);
    Init(tmp1, mid, mid);

    StrassenMultiplication(A11, subtract(B12, B22, tmp1, mid), R, mid);
    Init(tmp1, mid, mid);

    StrassenMultiplication(A22, subtract(B21, B11, tmp1, mid), S, mid);
    Init(tmp1, mid, mid);

    StrassenMultiplication(add(A11, A12, tmp1, mid), B22, T, mid);
    Init(tmp1, mid, mid);

    StrassenMultiplication(subtract(A21, A11, tmp1, mid), add(B11, B12, tmp2, mid), U, mid);
    Init(tmp1, mid, mid);
    Init(tmp2, mid, mid);

    StrassenMultiplication(subtract(A12, A22, tmp1, mid), add(B21, B22, tmp2, mid), V, mid);
    Init(tmp1, mid, mid);
    Init(tmp2, mid, mid);

    // Compute quadrants of C
    add(subtract(add(P, S, tmp1, mid), T, tmp2, mid), V, C11, mid);
    Init(tmp1, mid, mid);
    Init(tmp2, mid, mid);
    add(R, T, C12, mid);
    add(Q, S, C21, mid);
    add(subtract(add(P, R, tmp1, mid), Q, tmp2, mid), U, C22, mid);

    // Copy C into mat
    for (i = 0; i < mid; i++)
    {
        for (j = 0; j < mid; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

for (i = 0; i < mid; i++)
    {
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);

        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);

        free(C11[i]);
        free(C12[i]);
        free(C21[i]);
        free(C22[i]);

        free(P[i]);
        free(Q[i]);
        free(R[i]);
        free(S[i]);
        free(T[i]);
        free(U[i]);
        free(V[i]);

        free(tmp1[i]);
        free(tmp2[i]);
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);

    free(B11);
    free(B12);
    free(B21);
    free(B22);

    free(C11);
    free(C12);
    free(C21);
    free(C22);

    free(P);
    free(Q);
    free(R);
    free(S);
    free(T);
    free(U);
    free(V);

    free(tmp1);
    free(tmp2);
}

int main()
{
    srand(time(NULL));

    int min = 1, max = 16, numb;
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
    for (int i = 0; i < 16; i++)
    {
        arr_of_mat[i] = (int **)malloc(16 * sizeof(int *));
        for (int j = 0; j < 16; j++)
        {
            arr_of_mat[i][j] = (int *)malloc(16 * sizeof(int));
            // Initialize arr_of_mat[i][j] here
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
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
        printf("\n");
    }
    
    int **result2 = (int **)malloc(16 * sizeof(int *));
    int **prevRes = (int **)malloc(16 * sizeof(int *));
    for (int i = 0; i < 16; i++)
    {
        result2[i] = (int *)malloc(sizeof(int) * 16);
        prevRes[i] = (int *)malloc(sizeof(int) * 16);
    }
    
    int ** pre1 = arr_of_mat[0];
    int ** pre2 = arr_of_mat[1];
    // printf("pre1\n");
    // print_mat(sizes[0][0],sizes[0][1],pre1);
    // printf("pre2\n");
    // print_mat(sizes[1][0],sizes[1][1],pre2);
    
    Init(prevRes, sizes[0][0],sizes[1][1]);
    
    clock_t sttime2 = clock();
    StrassenMultiplication(pre1,pre2, prevRes, 16);
    // printf("\nprevRes: (%d x %d)\n", sizes[0][0], sizes[1][1]);
    // print_mat(sizes[0][0],sizes[1][1],prevRes);
    
    for (int i = 1; i < 9; i++)
    {
        int **matrix1 = arr_of_mat[i+1];
        Init(result2,16,16);
        StrassenMultiplication(prevRes, matrix1,result2,16);
        Init(prevRes,16,16);
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                prevRes[j][k] = result2[j][k];
            }
        }
        // printf("\n\nResult at step : %d\n\n",i+1);
        // print_mat(sizes[0][0],sizes[i+1][1],result2);
    }
    double time2 = (double)(clock() - sttime2) / CLOCKS_PER_SEC;

    printf("\nResultant Matrix (from method 2 - Linear and Strassen): (%d x %d)\n", sizes[0][0], sizes[9][1]);
    print_mat(sizes[0][0], sizes[9][1], result2);
    
    // Free the memory allocated for the matrices
    for (int i = 0; i < 16; i++)
    {
        free(result2[i]);
        free(prevRes[i]);
    }
    free(result2);
    free(prevRes);
    return 0;   
}
