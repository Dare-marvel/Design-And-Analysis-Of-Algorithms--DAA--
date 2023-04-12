// This code has been written by Adwait Purao
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

int **multiplyMatricesOptimalOrder(int ***matrices, int **kmat, int i, int j, int n)
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
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
            {
                for (int z = 0; z < n; z++)
                {
                    result[x][y] += left[x][z] * right[z][y];
                }
            }
        }
        return result;
    }
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

void print_mat_range(int k, int sizes[10][2], int ***arr_of_mat)
{
    printf("M%d (%d x %d)\n", k, sizes[k - 1][0], sizes[k - 1][1]);
    print_mat(sizes[k - 1][0], sizes[k - 1][1], arr_of_mat[k - 1]);
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

    int **result3;

    int **kmat = matrixChainMultiplication(randomNum, 10);
    printf("\n");
    printf("\n\nResultant Matrix (from method 3 - MCM and Regular): (%d x %d)\n", sizes[0][0], sizes[9][1]);
    result3 = multiplyMatricesOptimalOrder(arr_of_mat, kmat, 0, 9, 48);
    print_mat(sizes[0][0], sizes[9][1], result3);
    
    return 0;
}