### [15 Puzzle Problem](https://www.geeksforgeeks.org/8-puzzle-problem-using-branch-and-bound/)
### [Solvability of a 15 puzzle problem](https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/)

## Explanation of the main logic:
The solve() function uses the Branch and Bound algorithm to solve the N-puzzle problem. It takes the initial state of the puzzle, the coordinates of the blank tile (i.e., the tile that can be moved), and the final state of the puzzle as input parameters. The function creates a priority queue to store live nodes of the search tree, which are nodes that have been generated but have not yet been expanded.

The algorithm starts by creating a root node that represents the initial state of the puzzle. The cost of the root node is calculated as the number of misplaced tiles between the initial and final state of the puzzle. The root node is added to the priority queue.

The function then enters a loop that continues until the priority queue is empty. In each iteration of the loop, the node with the least estimated cost (i.e., the sum of its cost and level) is removed from the priority queue. If the removed node is an answer node (i.e., its cost is zero), the function prints the path from the root node to the answer node and returns.

If the removed node is not an answer node, the function generates its children nodes by moving the blank tile in all four possible directions (up, down, left, right) and creating a new node for each valid move. The cost of each child node is calculated as the number of misplaced tiles between the state of the puzzle represented by the child node and the final state of the puzzle.

The children nodes are then added to the priority queue. The loop continues until an answer node is found or the priority queue is empty.

Note that the priority queue is ordered based on the estimated cost of each node. This ensures that the algorithm explores nodes with lower estimated cost first, which is a heuristic that can improve the efficiency of the search.

## Time and Space Complexity:
### `Time Complexity`
The time complexity of the solve function depends on the size of the search space and the efficiency of the heuristic function. In the worst case, the algorithm explores the entire search space, which is of size `O(N^2 * N!)`. However, the use of the heuristic function reduces the size of the search space, and the algorithm typically runs much faster in practice. The time complexity of the algorithm can be expressed as `O(b^d)`, where b is the branching factor (i.e., the average number of moves available from each state) and d is the depth of the shallowest goal node.

### `Space Complexity`
The space complexity of the solve function is determined by the size of the priority queue used to store the live nodes of the search tree. The priority queue can hold at most `O(N^2).` nodes, so the space complexity of the algorithm is also O(b^d).

## Code:
```cpp
// Program to print path from root node to destination node
// for N*N -1 puzzle algorithm using Branch and Bound
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
#define N 4

// state space tree nodes
struct Node
{
	// stores the parent node of the current node
	// helps in tracing path when the answer is found
	Node* parent;

	// stores matrix
	int mat[N][N];

	// stores blank tile coordinates
	int x, y;

	// stores the number of misplaced tiles
	int cost;

	// stores the number of moves so far
	int level;
};

// Function to print N x N matrix
void printMatrix(int mat[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

// Function to allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX,
			int newY, int level, Node* parent)
{
	Node* node = new Node;

	// set pointer for path to root
	node->parent = parent;

	// copy data from parent node to current node
	memcpy(node->mat, mat, sizeof node->mat);

	// move tile by 1 position
	swap(node->mat[x][y], node->mat[newX][newY]);

	// set number of misplaced tiles
	node->cost = INT_MAX;

	// set number of moves so far
	node->level = level;

	// update new blank tile coordinates
	node->x = newX;
	node->y = newY;

	return node;
}

// bottom, left, top, right
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

// Function to calculate the number of misplaced tiles
// ie. number of non-blank tiles not in their goal position
int calculateCost(int initial[N][N], int final[N][N])
{
	int count = 0;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		if (initial[i][j] && initial[i][j] != final[i][j])
		count++;
	return count;
}

// Function to check if (x, y) is a valid matrix coordinate
int isSafe(int x, int y)
{
	return (x >= 0 && x < N && y >= 0 && y < N);
}

// print path from root node to destination node
void printPath(Node* root)
{
	if (root == NULL)
		return;
	printPath(root->parent);
	printMatrix(root->mat);

	printf("\n");
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
	}
};

// Function to solve N*N - 1 puzzle algorithm using
// Branch and Bound. x and y are blank tile coordinates
// in initial state
void solve(int initial[N][N], int x, int y,
		int final[N][N])
{
	// Create a priority queue to store live nodes of
	// search tree;
	priority_queue<Node*, std::vector<Node*>, comp> pq;

	// create a root node and calculate its cost
	Node* root = newNode(initial, x, y, x, y, 0, NULL);
	root->cost = calculateCost(initial, final);

	// Add root to list of live nodes;
	pq.push(root);

	// Finds a live node with least cost,
	// add its childrens to list of live nodes and
	// finally deletes it from the list.
	while (!pq.empty())
	{
		// Find a live node with least estimated cost
		Node* min = pq.top();

		// The found node is deleted from the list of
		// live nodes
		pq.pop();

		// if min is an answer node
		if (min->cost == 0)
		{
			// print the path from root to destination;
			printPath(min);
			return;
		}

		// do for each child of min
		// max 4 children for a node
		for (int i = 0; i < 4; i++)
		{
			if (isSafe(min->x + row[i], min->y + col[i]))
			{
				// create a child node and calculate
				// its cost
				Node* child = newNode(min->mat, min->x,
							min->y, min->x + row[i],
							min->y + col[i],
							min->level + 1, min);
				child->cost = calculateCost(child->mat, final);

				// Add child to list of live nodes
				pq.push(child);
			}
		}
	}
}

int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < 16 - 1; i++)
        for (int j = i+1; j < 16; j++)
             // Value 0 is used for empty space
             if (arr[j] && arr[i] &&  arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}
 
// This function returns true if given 8 puzzle is solvable.
bool isSolvable(int puzzle[4][4])
{
    // Count inversions in given 8 puzzle
    int invCount = getInvCount((int *)puzzle);
 
    // return true if inversion count is even.
    return (invCount%2 == 0);
}

// Driver code
int main() {
    int initial[N][N], final[N][N];
    int x, y;

    // take user input for the initial configuration
    cout << "Enter the initial configuration (0 for empty space):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initial[i][j];
        }
    }
    
    if(!isSolvable(initial)){
        cout << "\nNot Solvable\n";
        exit(0);
    }
                      
    // take user input for the final configuration
    cout << "\nEnter the final configuration (0 for empty space):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> final[i][j];
        }
    }

    // take user input for the blank tile coordinates in initial configuration
    cout << "Enter the blank tile coordinates (row column): ";
    cin >> x >> y;

    solve(initial, x, y, final);

    return 0;
}
```
