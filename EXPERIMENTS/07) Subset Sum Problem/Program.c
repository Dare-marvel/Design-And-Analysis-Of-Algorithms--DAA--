#include <stdio.h>

#define MAX_N 100

int w[MAX_N];  // array to store weights of n elements
int x[MAX_N];  // array to store the binary vector representing a subset
int n, m, sum; // n: number of elements, m: desired sum, sum: sum of elements in a subset

void backtrack(int i) {
    if (i == n) { // reached the end of the subset vector
        if (sum == m) { // subset sum matches desired sum
            printf("{ ");
            for (int j = 0; j < n; j++) {
                if (x[j]) printf("%d ", w[j]); // print elements of subset
            }
            printf("}\n");
        }
    } else {
        x[i] = 1; // include element i in subset
        sum += w[i];
        if (sum <= m) backtrack(i+1); // explore left child only if sum doesn't exceed m
        sum -= w[i];
        x[i] = 0; // exclude element i from subset
        backtrack(i+1); // explore right child
    }
}

int main() {
    printf("Enter the number of elements:");
    scanf("%d", &n);
    printf("Enter the weights of the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    printf("Enter the desired sum: ");
    scanf("%d", &m);
    backtrack(0);
    return 0;
}