### [MCM](https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/)
### [Strassen's Matrix Multiplication](https://www.geeksforgeeks.org/strassens-matrix-multiplication/)

## Brief Description:

## Key Insights:

## Code :
```c
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

    // Free memory
    free(tmp1);
    free(tmp2);
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
}

void printOptimalParentheses(int **kmat, int i, int j)
{
    if (i == j)
    {
        printf("M%d", (i));
    }
    else
    {
        printf("(");
        printOptimalParentheses(kmat, i, kmat[i][j]);
        printOptimalParentheses(kmat, kmat[i][j] + 1, j);
        printf(")");
    }
}

int **matrixChainMultiplication(int dims[], int n)
{
    int mat[n][n];
    int **kmat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        kmat[i] = (int *)malloc(n * sizeof(int));
    }
    int i, j, k, L, q;

    Init(kmat, n, n);
    // Cost is zero when multiplying one matrix
    for (i = 1; i < n; i++)
    {
        mat[i][i] = 0;
    }

    // L is length of the chain, which can go from 2 to n-1
    for (L = 2; L < n; L++)
    {
        for (i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            mat[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                q = mat[i][k] + mat[k + 1][j] + dims[i - 1] * dims[k] * dims[j];

                if (q < mat[i][j])
                {
                    mat[i][j] = q;
                    kmat[i][j] = k;
                }
            }
        }
    }

    printf("The least number of multiplications are: %d\n", mat[1][n - 1]);
    printf("The optimal order of parentheses is: ");
    printOptimalParentheses(kmat, 1, n - 1);
    printf("\n");

    return kmat;
}

int **strassenOptimalOrder(int ***matrices, int **kmat, int i, int j, int n)
{
    if (i == j)
    {
        int **result = (int **)malloc(n * sizeof(int *));
        for (int k = 0; k < n; k++)
        {
            result[k] = (int *)malloc(n * sizeof(int));
            memcpy(result[k], matrices[i][k], n * sizeof(int));
        }
        return result;
    }
    else
    {
        int **left = (int **)malloc(n * sizeof(int *));
        for (int x = 0; x < n; x++)
        {
            left[x] = (int *)malloc(n * sizeof(int));
            memset(left[x], 0, n * sizeof(int));
        }
        for (int x = 0; x < n; x++)
        {
            memcpy(left[x], matrices[i][x], n * sizeof(int));
        }

        int **right = (int **)malloc(n * sizeof(int *));
        for (int x = 0; x < n; x++)
        {
            right[x] = (int *)malloc(n * sizeof(int));
            memset(right[x], 0, n * sizeof(int));
        }
        for (int x = 0; x < n; x++)
        {
            memcpy(right[x], matrices[kmat[i][j] + 1][x], n * sizeof(int));
        }

        int **result = (int **)malloc(n * sizeof(int *));
        for (int k = 0; k < n; k++)
        {
            result[k] = (int *)malloc(n * sizeof(int));
            memset(result[k], 0, n * sizeof(int));
        }
        StrassenMultiplication(left,right,result,n);
        return result;
    }
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
    for (int i = 0; i < 10; i++)
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
                arr_of_mat[i][j][k] = 0;
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
    int **result = (int **)malloc(48 * sizeof(int *));
    for (int i = 0; i < 48; i++)
    {
        result[i] = (int *)malloc(48 * sizeof(int));
    }
    Init(result, 48, 48);
    int **kmat = matrixChainMultiplication(randomNum, 10);
    printf("\n");
    printf("\n\nResultant Matrix (from method 3 - MCM and Strassen): (%d x %d)\n", sizes[0][0], sizes[9][1]);
    result = strassenOptimalOrder(arr_of_mat, kmat, 0, 9, 48);
    print_mat(sizes[0][0], sizes[9][1], result);
    return 0;
}
```
## Output:
```c
Sizes
45 10 
10 41 
41 45 
45 17 
17 22 
22 3 
3 41 
41 29 
29 5 
5 37 

 Matrices:
M1 (45 x 10)
0 1 0 0 0 0 0 0 1 1 
0 0 0 1 0 1 0 0 0 1 
0 0 1 0 0 1 0 0 1 0 
0 1 1 1 0 1 1 0 1 1 
1 1 1 1 0 1 0 1 1 0 
0 1 0 1 1 0 0 1 1 0 
1 1 1 0 0 1 1 0 1 0 
1 0 0 0 1 0 1 1 1 0 
0 1 1 0 1 0 1 1 1 0 
1 0 1 1 0 0 0 1 0 0 
1 1 0 1 1 0 0 0 1 1 
0 1 1 1 0 0 1 1 1 0 
1 1 0 0 0 0 0 0 1 0 
0 0 1 1 0 0 1 0 0 0 
1 0 0 0 1 0 0 0 1 0 
0 0 1 0 0 1 0 1 1 1 
1 0 0 1 1 0 1 0 0 0 
0 1 0 0 0 0 0 0 0 1 
0 1 1 1 1 0 0 0 1 0 
1 0 0 1 1 1 1 1 1 1 
1 1 1 1 0 1 1 0 1 0 
0 0 1 1 1 0 1 0 0 0 
0 0 1 0 1 0 1 1 1 0 
0 0 1 1 0 1 0 1 0 0 
1 0 0 0 1 1 1 1 1 1 
1 1 1 0 1 1 1 0 0 0 
0 0 1 0 0 1 1 0 0 1 
0 0 1 0 0 1 0 1 0 1 
1 1 1 0 0 0 1 1 1 1 
1 1 0 0 1 0 1 1 0 0 
0 1 0 0 1 0 1 1 0 1 
1 1 0 0 1 0 0 1 1 1 
0 1 1 0 1 0 0 1 1 1 
1 0 0 1 0 1 1 1 1 1 
0 0 0 0 0 0 1 0 1 0 
0 1 1 1 0 1 1 0 0 1 
1 1 1 1 0 1 1 1 0 0 
1 0 0 1 0 0 1 1 0 0 
0 0 0 1 1 0 0 1 0 0 
0 0 1 1 1 1 0 0 1 0 
0 0 0 0 1 0 0 1 0 1 
1 0 1 1 1 1 1 0 0 0 
0 0 0 0 1 1 1 1 0 0 
1 0 0 1 1 0 1 1 1 1 
0 0 1 0 0 1 1 1 1 1 

M2 (10 x 41)
1 1 1 1 1 0 1 1 1 1 1 0 1 0 1 0 0 0 0 1 0 0 1 1 0 1 0 1 1 1 0 0 1 1 0 0 1 1 1 0 0 
1 0 1 1 1 0 1 0 0 0 0 0 1 1 1 1 0 0 0 1 1 0 0 0 0 1 0 1 0 0 1 1 1 1 0 0 1 1 0 1 1 
0 1 1 0 0 0 0 1 0 1 0 0 0 0 1 1 0 0 1 1 0 1 0 1 1 0 0 1 1 1 0 1 0 1 1 1 1 1 0 1 1 
0 0 1 0 1 0 1 1 1 0 1 0 0 0 0 0 0 1 1 1 1 1 0 1 0 1 0 0 1 0 1 1 0 0 1 1 0 0 0 1 0 
0 0 0 0 0 1 1 1 0 0 0 1 0 1 0 1 0 0 0 0 1 1 0 1 1 1 1 1 1 0 0 1 0 0 0 0 1 1 1 0 1 
0 1 0 1 1 1 1 1 0 1 0 1 1 1 0 0 0 0 0 1 0 1 1 0 1 0 0 0 1 0 0 1 1 0 1 1 1 0 0 1 0 
1 1 1 0 1 0 1 1 0 0 1 1 1 0 1 1 0 1 1 0 1 0 1 1 1 0 1 0 1 0 0 0 1 1 0 1 1 1 0 1 1 
0 1 1 0 0 0 0 1 1 0 1 0 1 0 1 0 1 1 1 0 1 1 1 1 1 0 0 1 1 0 0 1 1 1 1 1 0 1 0 1 1 
1 1 0 0 1 0 1 0 1 1 0 0 1 1 0 1 1 1 0 1 1 1 0 1 0 1 1 1 0 0 0 1 0 1 1 1 1 1 1 1 0 
1 1 1 0 1 1 0 0 1 1 0 1 0 1 1 1 0 1 1 0 1 1 0 0 0 1 0 1 1 1 0 0 0 1 1 0 0 1 0 0 0 

M3 (41 x 45)
0 1 0 1 0 0 1 1 1 0 1 0 0 1 1 0 1 0 1 0 0 1 1 0 0 1 0 1 1 0 0 0 1 0 1 0 0 1 1 0 1 0 0 1 0 
1 1 1 0 0 0 0 0 1 0 0 0 1 0 1 1 0 1 1 0 1 1 1 0 0 1 1 1 1 0 1 1 0 0 1 0 0 1 0 1 0 1 1 1 1 
1 0 1 0 1 1 1 0 0 1 1 1 0 0 1 1 1 0 1 1 1 1 0 0 0 1 0 1 1 1 0 0 0 1 0 1 0 0 0 1 1 1 0 0 1 
1 1 0 1 0 1 0 1 1 1 1 1 1 0 0 1 0 0 1 1 0 0 0 0 0 1 0 1 1 0 0 1 1 0 0 1 0 1 0 1 0 0 0 1 0 
0 0 1 0 1 0 1 0 0 1 0 1 1 0 1 1 0 0 0 1 0 1 1 1 0 0 1 0 1 1 0 1 1 1 0 1 0 1 1 0 0 1 0 0 1 
1 1 0 1 0 1 1 1 0 1 1 0 0 1 1 1 0 1 1 1 1 0 1 0 1 0 0 0 0 0 0 1 0 0 0 0 1 1 1 1 0 1 1 1 0 
1 0 0 0 1 0 1 1 1 1 0 1 1 1 1 0 1 0 0 1 0 0 0 0 1 1 0 0 0 1 1 1 0 1 1 1 1 0 1 1 1 1 0 1 0 
0 1 1 0 1 0 1 1 0 1 0 1 1 1 0 1 0 1 1 1 1 0 1 1 1 0 1 1 0 0 1 0 1 1 1 0 1 0 1 0 1 1 1 0 0 
1 1 0 1 0 0 0 1 1 1 0 1 0 1 1 0 1 0 1 0 1 1 1 1 0 1 0 0 1 0 0 0 0 1 1 0 1 1 1 0 1 0 1 1 1 
0 0 0 0 1 0 1 1 0 0 1 1 0 1 0 1 0 1 1 1 0 1 0 0 1 0 1 1 1 0 0 1 0 1 0 0 1 1 1 1 0 0 1 0 0 
1 1 0 0 0 1 1 0 1 1 1 1 0 0 0 0 0 1 1 1 1 1 1 1 0 0 1 0 1 1 0 1 1 0 1 1 1 0 1 0 1 0 1 1 0 
1 0 1 1 1 0 0 0 1 1 0 0 0 0 1 0 1 0 1 1 0 0 1 0 0 1 0 0 1 1 1 0 1 0 1 0 0 0 0 0 1 0 0 0 1 
1 0 0 0 1 1 0 1 0 0 1 0 0 0 1 0 1 1 1 1 1 0 1 1 0 1 0 1 1 0 0 1 0 0 1 1 1 1 1 0 1 0 0 0 0 
1 0 1 0 1 0 1 1 0 0 0 1 1 1 1 1 1 0 0 1 1 1 0 0 0 0 1 1 0 1 1 1 1 1 0 1 1 1 0 1 0 0 1 1 1 
0 0 0 0 0 1 1 0 0 1 0 0 0 1 1 0 1 0 1 0 0 0 1 0 1 1 0 1 0 1 1 0 1 1 0 0 1 1 0 1 0 0 1 0 0 
0 0 1 1 0 1 1 0 0 1 1 1 1 1 1 0 0 1 0 1 1 0 0 0 0 1 0 0 1 1 0 1 1 1 0 1 0 0 0 1 1 1 0 1 0 
0 1 0 1 1 0 1 1 0 1 1 0 0 0 1 1 0 0 0 0 1 0 0 1 0 1 0 1 0 1 0 0 1 0 1 0 0 0 0 1 0 1 1 0 1 
0 1 0 0 1 0 1 1 0 0 1 0 1 1 0 0 1 0 1 1 1 0 0 0 0 1 0 1 0 0 1 0 1 1 0 0 1 0 0 1 0 1 1 1 0 
1 0 1 1 1 1 1 1 1 1 1 0 1 1 0 1 0 0 0 1 0 0 0 0 0 1 1 0 1 0 0 0 0 0 0 0 1 1 1 0 0 1 0 1 0 
0 0 0 0 0 1 0 0 1 1 1 0 0 1 1 0 1 0 1 1 0 1 0 1 0 0 1 1 0 0 1 0 0 1 0 0 0 1 0 1 0 1 0 0 0 
1 0 0 1 1 1 1 0 0 0 1 0 1 0 1 1 0 1 1 1 0 1 0 1 0 1 1 1 1 1 0 1 1 0 0 1 1 0 1 1 0 0 0 0 1 
1 1 1 0 1 0 0 0 0 1 0 0 0 0 1 1 0 0 1 0 1 0 1 1 1 1 1 0 1 1 1 0 1 0 0 0 0 1 0 1 0 1 1 1 1 
0 0 1 1 1 1 0 1 0 1 1 1 0 1 0 0 0 0 1 0 1 1 0 0 1 1 0 0 0 1 1 1 0 0 0 1 1 0 1 0 1 0 1 1 1 
0 1 1 0 0 1 1 1 1 1 1 1 0 1 1 1 1 0 1 1 0 1 1 0 0 1 1 0 0 1 1 0 0 0 1 1 1 0 0 0 0 1 1 0 1 
1 1 0 1 1 1 0 0 0 0 0 1 0 0 0 1 1 0 1 1 1 0 0 0 1 0 0 0 0 0 1 1 1 1 0 0 1 0 0 1 1 0 1 1 0 
1 0 1 1 1 0 1 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 0 0 0 1 0 1 1 0 0 0 0 1 0 1 0 1 0 1 1 
1 0 0 1 1 0 1 0 0 0 1 1 0 1 1 1 0 0 0 0 0 1 0 0 1 1 0 1 1 0 0 0 0 0 1 1 0 1 1 0 1 1 1 0 0 
0 1 0 0 0 0 1 1 1 1 0 0 1 1 0 1 1 0 0 1 0 1 0 1 1 0 0 0 0 0 0 0 0 1 1 0 1 0 1 0 1 1 1 0 1 
1 0 0 1 0 0 1 1 0 0 0 0 1 0 0 1 1 1 1 0 0 1 1 0 0 0 1 0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 0 0 0 
0 0 1 1 1 1 1 1 0 1 1 0 0 1 1 0 0 1 1 0 1 1 1 0 0 1 1 1 1 0 1 1 0 0 1 1 1 0 0 0 0 0 0 0 1 
0 0 0 1 0 0 0 1 1 0 1 0 0 0 1 0 0 1 0 0 0 1 0 0 0 0 0 0 0 1 1 0 1 1 0 1 1 0 0 1 1 1 1 1 0 
1 1 0 0 1 0 0 0 0 0 0 0 1 0 1 0 0 1 1 1 1 1 1 0 1 0 1 1 1 0 1 0 1 1 0 0 1 0 0 0 1 1 0 0 1 
1 0 1 1 1 1 0 0 0 0 0 0 1 1 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 1 0 0 1 1 1 0 0 0 0 0 0 0 0 1 
1 1 1 1 0 0 0 0 0 1 1 1 1 1 0 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 1 0 0 1 0 1 0 0 0 1 1 
0 0 0 0 1 0 0 1 0 0 0 0 1 0 0 1 0 0 1 0 1 1 1 0 0 0 0 0 0 1 1 0 1 0 0 0 0 1 1 1 1 1 1 0 0 
0 0 0 0 1 0 1 1 1 1 1 1 1 1 1 0 0 1 1 0 0 1 1 1 0 0 0 0 1 1 0 1 1 0 1 0 0 0 1 0 1 0 1 0 1 
1 0 0 0 1 0 0 0 1 1 1 1 0 1 1 1 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 1 0 0 0 0 1 1 0 0 0 1 0 1 
0 1 0 1 1 1 1 0 0 1 0 0 1 0 1 0 0 1 1 0 1 1 1 0 0 1 1 0 0 1 1 1 1 1 0 0 0 1 0 1 0 0 1 0 1 
0 0 1 1 1 0 0 0 1 1 1 0 0 1 0 1 1 1 0 0 1 1 1 0 1 0 1 0 1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1 1 
0 1 0 1 1 0 1 0 1 1 0 1 0 0 0 1 1 1 0 1 1 0 0 0 1 1 1 0 1 1 1 1 0 1 0 1 0 1 0 1 1 0 1 1 0 
1 1 1 1 1 0 0 0 0 0 1 0 0 1 1 1 1 0 1 0 0 0 0 0 0 0 1 0 1 0 0 0 1 1 1 1 0 0 1 0 0 0 0 0 1 

M4 (45 x 17)
1 1 0 1 0 1 0 1 1 0 1 1 1 0 0 1 0 
1 1 0 0 0 0 0 1 0 1 1 1 1 0 0 1 1 
0 1 0 0 0 1 0 0 1 1 0 1 0 0 0 1 0 
1 1 0 1 0 1 0 1 0 0 0 0 1 1 0 0 1 
0 1 0 0 1 1 1 1 1 0 1 1 1 0 0 1 0 
0 1 1 0 1 1 0 1 0 1 0 0 0 1 1 1 1 
1 0 1 1 1 0 1 0 1 0 0 0 1 1 0 1 0 
0 0 0 1 1 0 0 1 0 0 0 1 1 1 1 1 0 
0 0 0 1 1 0 1 1 0 1 0 0 0 1 0 0 1 
1 1 1 0 0 1 0 0 1 0 1 0 1 0 0 0 0 
1 1 0 0 0 0 1 1 0 1 0 1 1 1 0 0 0 
0 0 1 1 0 0 1 0 0 0 0 0 0 0 1 1 1 
0 0 1 1 1 0 1 1 1 0 0 1 1 0 0 1 1 
1 0 0 0 0 0 0 0 1 1 0 0 0 1 0 0 1 
0 1 1 1 0 0 1 0 1 0 0 1 0 0 0 0 0 
0 0 0 1 0 1 0 0 0 0 0 0 1 1 0 0 0 
1 1 0 1 1 1 1 0 1 1 0 1 1 0 0 1 0 
1 1 0 1 0 0 1 0 0 0 1 1 1 1 0 0 1 
1 1 0 1 1 1 0 1 1 0 1 1 1 0 0 1 0 
1 1 0 0 1 0 1 0 1 0 1 0 0 0 1 1 0 
0 1 0 1 0 1 1 0 0 0 0 0 1 0 1 0 0 
1 1 0 0 1 0 0 0 0 0 0 1 0 1 0 1 1 
1 1 0 0 1 0 0 1 0 0 1 1 0 1 0 0 0 
1 1 0 1 0 0 0 0 1 0 1 1 1 0 0 0 0 
0 0 0 1 1 0 1 1 1 1 0 0 1 0 1 1 0 
0 1 0 0 1 0 0 1 1 1 1 0 0 0 0 0 0 
1 1 1 0 0 0 0 1 0 1 1 1 0 0 0 1 0 
0 1 0 1 0 0 0 1 0 0 1 0 0 0 0 0 1 
0 0 1 0 1 0 0 1 1 0 1 1 0 1 0 1 0 
1 1 0 1 0 0 0 0 0 0 0 0 0 1 1 1 0 
1 0 0 1 1 0 0 0 1 0 0 1 1 0 0 0 0 
0 0 0 0 0 0 0 0 1 1 1 0 0 0 1 0 0 
1 0 0 1 0 0 1 0 1 0 0 0 0 0 0 0 0 
0 1 1 0 1 0 1 1 0 1 1 1 0 1 0 0 0 
1 0 0 0 1 1 0 1 1 0 0 1 1 0 1 0 1 
0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 
1 0 0 0 0 0 0 0 1 1 0 1 1 0 1 1 1 
0 1 1 1 1 0 0 0 1 1 1 0 1 0 0 1 0 
0 1 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 
0 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0 1 
1 1 1 1 1 0 0 1 0 1 1 0 1 1 0 0 0 
1 1 0 1 1 0 0 1 1 0 1 1 0 0 0 0 1 
1 1 1 0 1 1 1 0 0 0 1 0 0 1 1 1 1 
0 0 0 0 1 1 1 0 0 1 1 1 1 0 0 1 0 
0 0 1 1 0 1 1 1 0 1 1 1 0 0 0 0 0 

M5 (17 x 22)
0 1 1 1 0 0 1 1 1 0 1 1 1 1 0 1 1 1 1 0 1 1 
0 0 0 0 1 0 0 1 1 0 1 0 0 1 0 1 0 1 1 1 1 1 
1 1 0 0 0 0 0 1 1 1 0 1 1 1 1 1 0 0 1 1 1 1 
0 1 0 0 1 0 0 0 1 1 1 1 1 1 1 1 1 0 0 1 1 1 
0 1 0 0 1 0 0 0 1 0 0 0 1 1 0 1 1 1 0 0 0 1 
1 0 0 0 0 1 1 0 0 1 1 1 0 0 1 0 1 0 0 1 0 1 
0 0 0 1 1 0 1 0 1 0 0 0 1 0 1 0 0 1 0 1 0 0 
0 1 0 1 0 0 0 0 0 0 1 0 1 0 1 0 0 0 0 0 0 1 
1 1 0 1 1 0 1 1 0 1 1 0 0 1 0 0 1 0 0 0 1 1 
1 0 1 1 0 1 0 1 1 1 0 1 0 1 1 1 1 1 0 0 1 0 
1 1 0 0 0 0 1 1 1 0 1 0 1 1 0 1 0 1 0 1 0 1 
0 1 0 1 0 1 1 1 1 0 0 0 1 0 0 0 1 0 0 0 0 1 
0 0 1 0 1 1 1 1 0 0 0 1 1 0 0 1 1 1 1 0 1 0 
0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 1 0 0 0 0 
1 0 1 0 1 0 0 1 1 1 1 1 1 1 0 1 1 0 0 0 1 1 
1 1 1 1 0 0 1 0 0 0 0 1 1 0 1 1 1 0 0 0 0 1 
1 0 1 0 0 1 1 1 0 0 0 1 1 1 1 0 1 1 1 0 0 0 

M6 (22 x 3)
0 0 1 
1 0 0 
1 0 1 
0 0 0 
0 0 1 
1 1 1 
1 0 1 
0 1 0 
1 0 0 
0 0 0 
0 0 0 
1 1 1 
1 0 1 
1 0 0 
1 1 0 
1 0 0 
0 0 0 
1 0 1 
0 1 1 
0 1 0 
0 1 0 
1 1 0 

M7 (3 x 41)
0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 1 1 1 0 1 1 1 1 1 0 0 0 1 0 0 
1 1 0 0 1 0 0 0 1 0 1 0 0 1 0 0 0 1 0 1 0 1 0 0 0 0 0 1 0 1 1 1 0 0 1 1 0 1 0 0 1 
1 0 1 0 0 0 0 0 0 1 0 1 1 0 0 0 1 1 0 0 0 1 0 0 1 1 1 0 1 1 0 0 1 1 0 1 1 1 1 1 0 

M8 (41 x 29)
0 1 0 0 1 0 1 0 0 1 0 1 1 1 0 1 0 1 0 1 1 1 0 0 1 1 0 0 1 
1 1 1 0 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 0 1 0 1 0 0 1 0 1 1 
0 0 1 1 1 1 0 1 1 1 0 0 0 0 0 1 0 1 0 1 0 0 1 0 1 1 0 0 1 
0 0 0 0 1 1 0 0 0 1 1 1 1 0 0 1 0 1 0 0 1 1 0 1 0 1 0 0 1 
0 1 1 0 1 0 1 1 0 0 1 1 1 0 0 1 0 1 0 1 1 0 0 1 0 1 1 1 1 
1 1 0 1 0 0 0 0 0 1 0 0 0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 
1 0 0 0 0 1 0 1 0 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 1 
0 0 0 0 1 0 1 0 0 0 0 1 1 0 1 0 0 0 0 1 0 0 1 0 0 1 0 0 0 
1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 0 0 0 0 0 1 1 0 1 0 0 1 1 0 
1 1 0 0 1 0 1 0 1 0 1 0 0 1 0 1 1 0 1 0 0 1 1 1 1 0 0 0 1 
1 0 1 1 0 1 0 0 1 0 1 1 0 0 1 1 0 0 0 1 1 0 1 0 1 1 0 1 1 
0 1 0 0 0 1 1 1 0 1 0 0 1 0 0 1 1 1 1 0 0 0 1 0 0 0 0 1 0 
1 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 1 1 0 0 0 0 0 1 1 1 1 1 1 
0 1 0 0 1 1 0 0 1 0 1 1 0 0 0 1 0 0 0 1 0 0 0 0 1 1 0 0 0 
1 1 0 1 1 0 0 0 0 0 0 1 0 1 1 0 1 0 1 0 0 0 0 1 0 1 0 1 1 
0 1 0 1 1 1 0 1 0 1 0 0 1 1 0 0 0 1 0 1 0 0 1 0 0 0 1 1 0 
0 0 0 0 1 1 1 0 0 1 0 1 1 1 0 0 1 0 0 0 0 1 0 0 1 1 1 1 0 
0 0 0 1 0 0 0 0 0 0 0 1 1 1 0 0 1 0 1 1 0 0 0 0 0 0 1 1 1 
0 1 0 0 0 1 1 0 1 1 0 1 1 1 0 0 1 0 1 1 0 0 0 0 0 0 0 1 1 
0 0 1 1 0 0 1 1 1 0 0 0 0 0 1 0 0 1 1 1 0 1 1 0 1 1 1 1 1 
0 0 1 0 1 1 1 1 0 0 0 0 1 0 1 1 1 1 1 0 0 0 0 1 1 1 0 0 0 
1 0 0 1 1 0 1 0 1 0 1 0 1 1 1 1 0 0 1 1 1 1 0 0 0 1 1 1 0 
0 1 1 0 1 1 1 1 0 0 1 0 1 1 1 0 0 1 1 0 0 0 1 1 0 1 1 0 1 
0 0 1 1 1 1 0 0 0 0 0 0 1 1 1 0 0 0 0 1 1 0 1 1 1 1 0 1 0 
0 0 1 0 1 0 1 0 1 0 0 1 0 1 0 1 0 0 0 0 0 1 1 0 1 1 1 0 1 
0 0 1 0 1 1 1 0 0 1 1 0 0 0 1 1 0 0 1 0 0 0 0 0 1 0 1 0 1 
1 1 0 1 0 0 1 1 0 1 0 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 1 0 1 
0 1 0 1 1 0 0 0 1 1 0 0 1 1 0 0 1 0 1 1 0 1 1 0 0 1 0 0 1 
0 0 1 1 0 0 1 0 0 1 1 0 1 1 1 0 1 1 1 1 1 1 1 0 0 1 0 0 1 
1 1 1 1 0 1 1 0 0 0 1 1 1 1 0 1 0 0 0 0 0 0 1 1 1 1 1 1 0 
1 0 1 0 0 0 0 1 1 1 1 1 0 0 1 1 0 0 1 0 0 1 0 0 0 1 0 0 1 
1 0 0 1 1 1 1 1 1 0 0 0 1 0 0 1 1 1 1 1 1 0 1 0 0 0 1 0 0 
1 1 1 1 1 0 0 0 0 1 0 0 1 0 0 1 1 1 0 0 1 1 1 1 1 0 1 1 1 
1 1 0 0 0 1 0 0 1 0 0 0 0 1 1 1 1 1 0 0 1 0 1 1 0 0 0 0 0 
1 1 1 0 1 0 0 0 0 0 1 0 1 1 1 0 0 0 1 1 0 1 1 0 1 0 0 1 0 
0 1 1 1 1 1 0 1 1 0 1 1 1 1 0 0 0 0 1 0 1 0 0 1 1 1 0 1 1 
1 1 0 1 0 1 0 1 0 1 0 0 0 0 0 1 0 0 0 1 1 0 0 0 1 1 1 0 1 
1 1 1 0 1 0 1 1 0 0 1 1 1 1 1 1 1 0 1 0 0 0 1 1 1 1 0 0 1 
0 0 0 1 1 0 1 1 1 0 1 0 1 0 1 0 1 0 0 1 1 0 0 0 1 1 1 1 1 
1 0 1 1 0 0 0 0 1 1 0 1 0 0 0 0 1 1 1 1 1 1 0 1 1 0 0 0 1 
1 1 1 1 0 0 1 0 1 0 0 0 0 1 1 0 0 1 1 1 1 0 0 0 0 1 1 1 1 

M9 (29 x 5)
1 0 1 0 1 
0 0 0 0 0 
1 0 0 1 0 
0 0 0 0 0 
1 1 1 1 1 
1 1 0 0 0 
1 1 1 0 1 
0 1 1 0 1 
1 1 1 0 1 
1 0 1 1 0 
1 0 1 0 1 
0 1 0 0 1 
1 1 0 0 0 
1 0 1 0 1 
0 0 0 1 0 
1 0 0 1 1 
0 0 1 1 1 
0 1 0 0 1 
0 1 0 0 1 
0 0 0 1 0 
1 1 0 1 0 
0 1 0 0 0 
1 0 0 0 1 
1 0 0 0 1 
1 0 0 0 0 
0 0 0 0 0 
1 1 1 1 0 
0 0 1 0 0 
1 0 1 0 0 

M10 (5 x 37)
0 1 1 1 1 0 0 1 0 0 0 0 1 0 0 1 1 1 0 1 0 0 1 1 1 1 1 1 0 1 1 1 0 0 0 0 0 
0 1 1 1 1 1 0 0 0 1 1 1 1 0 1 0 1 1 1 1 0 0 1 1 1 0 1 0 0 1 0 1 1 1 0 0 1 
0 0 1 1 0 0 0 0 0 0 0 1 1 1 1 1 0 0 1 1 1 1 1 1 1 0 0 1 0 0 0 0 1 1 1 1 1 
0 1 1 0 1 0 0 0 1 1 1 1 0 0 1 1 1 0 1 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 1 1 0 
1 0 0 0 1 1 1 1 0 0 0 0 1 0 0 1 1 1 1 0 0 0 0 1 1 1 1 1 0 0 1 1 0 1 1 1 1 

The least number of multiplications are: 16209
The optimal order of parentheses is: ((M1(M2(M3(M4(M5M6)))))((M7M8)M9))



Resultant Matrix (from method 3 - MCM and Strassen): (45 x 37)
2 1 0 1 2 0 1 0 0 1 0 0 1 2 0 2 0 0 1 1 0 1 0 0 0 2 0 2 1 0 1 1 0 2 1 0 1 
1 1 0 0 2 0 1 1 0 1 1 0 0 1 0 1 0 0 2 1 0 2 0 0 0 2 0 1 2 0 1 1 0 1 2 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 2 0 1 4 0 3 2 0 1 2 0 2 2 0 3 0 0 3 2 0 2 1 0 1 3 0 2 3 0 2 2 0 3 2 0 2 
2 2 0 2 3 0 3 3 0 1 3 0 3 1 0 1 1 0 2 3 0 2 2 0 1 3 0 3 3 0 2 3 0 3 2 0 2 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 2 0 2 3 0 3 2 0 1 2 0 3 1 0 2 0 0 1 2 0 0 2 0 1 2 0 2 2 0 1 1 0 3 0 0 3 
2 3 0 1 2 0 3 4 0 1 3 0 3 1 0 2 1 0 2 1 0 2 3 0 3 2 0 3 4 0 0 2 0 3 1 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 2 0 1 2 0 2 3 0 1 3 0 2 0 0 0 1 0 2 2 0 2 2 0 1 2 0 2 3 0 1 2 0 2 2 0 1 
3 2 0 2 4 0 4 3 0 2 2 0 2 3 0 3 0 0 2 3 0 3 1 0 1 5 0 4 4 0 2 3 0 3 2 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
2 1 0 2 2 0 2 1 0 1 1 0 2 1 0 1 0 0 0 2 0 0 1 0 0 2 0 2 1 0 1 1 0 2 0 0 2 
1 1 0 0 2 0 2 2 0 0 2 0 1 0 0 1 0 0 2 1 0 1 1 0 1 1 0 0 2 0 1 1 0 1 1 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 2 0 0 1 0 0 1 0 1 1 0 1 1 0 1 1 0 2 0 0 2 1 0 1 1 0 2 2 0 0 1 0 2 2 0 0 
2 2 0 1 3 0 4 4 0 1 3 0 2 1 0 2 0 0 2 2 0 2 2 0 2 3 0 2 4 0 1 2 0 2 1 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 0 0 1 2 0 3 2 0 0 1 0 1 2 0 2 0 0 1 2 0 2 0 0 1 3 0 2 2 0 2 3 0 1 1 0 2 
3 4 0 1 4 0 4 5 0 2 4 0 3 2 0 3 1 0 4 2 0 4 3 0 3 4 0 4 6 0 1 3 0 4 3 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 1 0 0 2 0 3 3 0 0 2 0 1 1 0 2 0 0 2 1 0 2 1 0 2 2 0 1 3 0 1 2 0 1 1 0 2 
1 2 0 0 1 0 2 3 0 0 2 0 2 1 0 2 1 0 2 0 0 2 2 0 3 1 0 2 3 0 0 2 0 2 1 0 2 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 4 0 1 3 0 3 4 0 2 3 0 3 2 0 3 1 0 3 1 0 3 3 0 3 3 0 4 5 0 0 2 0 4 2 0 3 
3 2 0 2 3 0 4 3 0 1 2 0 3 2 0 3 0 0 1 2 0 1 2 0 2 3 0 3 3 0 1 2 0 3 0 0 4 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 2 0 0 1 0 0 1 0 1 1 0 1 1 0 1 1 0 2 0 0 2 1 0 1 1 0 2 2 0 0 1 0 2 2 0 0 
4 4 0 2 4 0 3 3 0 2 3 0 4 2 0 3 1 0 3 2 0 2 3 0 2 3 0 4 4 0 1 2 0 5 2 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 3 0 1 3 0 3 3 0 1 2 0 3 3 0 4 1 0 3 1 0 3 2 0 3 3 0 4 4 0 1 3 0 4 2 0 3 
3 3 0 2 3 0 3 3 0 2 2 0 3 3 0 3 1 0 2 2 0 3 2 0 2 4 0 5 4 0 1 3 0 4 2 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 4 0 1 4 0 3 4 0 2 4 0 3 1 0 2 1 0 4 2 0 3 3 0 2 3 0 3 5 0 1 2 0 4 3 0 2 
1 1 0 0 1 0 1 1 0 0 1 0 1 0 0 1 0 0 1 0 0 0 1 0 1 0 0 0 1 0 0 0 0 1 0 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 3 0 2 4 0 4 4 0 1 4 0 4 1 0 2 1 0 3 3 0 2 3 0 2 3 0 3 4 0 2 3 0 4 2 0 3 
2 3 0 1 3 0 3 4 0 1 4 0 3 0 0 1 1 0 3 2 0 2 3 0 2 2 0 2 4 0 1 2 0 3 2 0 2 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 2 2 0 0 1 0 0 1 0 1 0 0 1 1 0 2 0 0 1 2 0 1 2 0 1 2 0 0 1 0 1 
1 2 0 0 1 0 1 2 0 1 1 0 1 2 0 2 1 0 2 0 0 3 1 0 2 2 0 3 3 0 0 2 0 2 2 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 2 0 0 1 0 2 3 0 0 2 0 2 1 0 2 1 0 2 0 0 2 2 0 3 1 0 2 3 0 0 2 0 2 1 0 2 
3 4 0 1 4 0 4 5 0 2 4 0 3 2 0 3 1 0 4 2 0 4 3 0 3 4 0 4 6 0 1 3 0 4 3 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
```
