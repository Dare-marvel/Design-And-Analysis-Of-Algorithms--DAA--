### [Subset Sum Problem](https://www.geeksforgeeks.org/subset-sum-problem/)

## Explanation of BackTrack function
The backtrack function is the core of the code, and it uses recursion to generate all possible subsets of the input set and check if the sum of each subset matches the desired sum.

The function takes an index i as input, which represents the current element in the subset vector x that is being explored. If i equals n, which is the number of elements in the input set, the function has reached the end of the subset vector, and it checks if the current subset's sum matches the desired sum m. If the condition is true, the function prints the subset's elements. Otherwise, the function returns without printing anything.

If i is less than n, the function first includes the ith element in the subset by setting x[i] to 1 and increments the sum sum by the ith element's weight w[i]. Then, it recursively calls the backtrack function with the next index i+1 only if the new sum is less than or equal to the desired sum m. The new sum is compared with the desired sum m to avoid exploring the left child if the new sum exceeds the desired sum. It does not make sense to continue exploring the left child if the sum of the current subset is already greater than the desired sum.

If the new sum is less than or equal to the desired sum, the function explores the left child by calling backtrack(i+1). At this point, the function has included the ith element in the current subset and is looking for all possible subsets that include this element.

After the left child exploration is complete, the function backtracks by excluding the ith element from the subset by setting x[i] to 0 and subtracting the ith element's weight w[i] from the sum sum. Then, it explores the right child by calling backtrack(i+1). At this point, the function has excluded the ith element in the current subset and is looking for all possible subsets that do not include this element.

This process continues until all possible subsets of the input set are explored. The backtrack function explores the search tree recursively and prunes the branches that exceed the desired sum. The output of the function is all the subsets of the input set whose sum matches the desired sum.

## Time and Space Complexity :
`Time Complexity`<br>
The time complexity of the backtrack function is O(2^n), where n is the number of elements in the input set. This is because the function explores all possible subsets of the input set, which is a binary tree with 2^n nodes. Each node in the tree represents a subset of the input set.

`Space Complexity`<br>
The space complexity of the function is O(n), where n is the number of elements in the input set. This is because the function uses two arrays of size n to store the binary vector representing a subset and the weights of the n elements. Additionally, the function uses three integer variables to store the current element index, the desired sum, and the sum of elements in a subset. The function does not use any additional data structures or variables, so the space complexity is linear in n.

## Code:
```c
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
```
