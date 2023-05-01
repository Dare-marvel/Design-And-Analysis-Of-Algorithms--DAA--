### [Convex Hull](https://www.geeksforgeeks.org/convex-hull-using-divide-and-conquer-algorithm/)

## Explanation of the Code:

The given code implements two algorithms to solve the closest pair of points problem, i.e., given a set of points in a 2-D plane, find the pair of points that are closest to each other. The two algorithms implemented are:

* Brute force algorithm: It checks all possible pairs of points and finds the pair with the minimum distance between them. This algorithm has a time complexity of O(n^3), where n is the number of points.
* Divide and conquer algorithm: It divides the set of points into two halves, recursively finds the closest pair in each half, and merges the two halves by finding the closest pair in the strip between the two halves. This algorithm has a time complexity of O(nlogn).

The code defines a structure "Point" to represent a point in 2-D space and implements a function "dist" to calculate the Euclidean distance between two points. The "orientation" function is used to find the orientation of three points (clockwise, counterclockwise, or collinear) and is used in the implementation of the Graham's Scan algorithm, which is used to find the convex hull of the set of points in the divide and conquer algorithm. The "graham_scan" function implements the Graham's Scan algorithm and returns the perimeter of the convex hull of the set of points. The "min" function finds the minimum distance between all possible pairs of points in a set of points. The "divide_and_conquer" function implements the divide and conquer algorithm and returns the closest pair of points in the set of points. The main function generates a set of 50 random points and calls both the algorithms to find the closest pair of points and prints the output.

## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_POINTS 2000

// Structure to represent a point in 2-D plane
typedef struct
{
    int x;
    int y;
} Point;

// Calculate Euclidean distance between two points
double dist(Point p1, Point p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

void bruteforce(Point arr[])
{
    for (int i = 0; i < 50; i++)
    {
        int x1 = arr[i].x;
        int y1 = arr[i].y;
        for (int j = i + 1; j < 50; j++)
        {
            int x2 = arr[j].x;
            int y2 = arr[j].y;
            int flag1 = 0, flag2 = 0;
            for (int k = 0; k < 50; k++)
            {
                int x = arr[k].x;
                int y = arr[k].y;
                int eqn = ((y - y1) * (x2 - x1)) - ((y2 - y1) * (x - x1));
                if (eqn > 0)
                {
                    flag1 = 1;
                }
                if (eqn < 0)
                {
                    flag2 = 1;
                }
            }
            if ((flag1 == 1 && flag2 == 0) || (flag1 == 0 && flag2 == 1))
            {
                printf("(%d,%d),(%d,%d)\n", x1, y1, x2, y2);
            }
        }
    }
}

// Orientation of three points (clockwise, counterclockwise, or collinear)
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
    {
        return 0;
    }
    else if (val > 0)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

// Graham's Scan algorithm
double graham_scan(Point points[], int n)
{

    // Find point with smallest y-coordinate
    Point start = points[0];
    for (int i = 1; i < n; i++)
    {
        if (points[i].y < start.y || (points[i].y == start.y && points[i].x < start.x))
        {
            start = points[i];
        }
    }

    // Sort remaining points by angle
    for (int i = 0; i < n; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            int o = orientation(start, points[min_idx], points[j]);
            if (o == 2 || (o == 0 && dist(start, points[j]) < dist(start, points[min_idx])))
            {
                min_idx = j;
            }
        }
        Point temp = points[i];
        points[i] = points[min_idx];
        points[min_idx] = temp;
    }

    // Build convex hull
    Point hull[MAX_POINTS];
    int top = 1;
    hull[0] = start;
    hull[1] = points[1];
    for (int i = 2; i < n; i++)
    {
        while (top >= 1 && orientation(hull[top - 1], hull[top], points[i]) != 2)
        {
            top--;
        }
        top++;
        hull[top] = points[i];
    }

    // Calculate perimeter of convex hull
    double perim = 0;
    for (int i = 0; i < top; i++)
    {
        perim += dist(hull[i], hull[i + 1]);
    }
    perim += dist(hull[top], start);

    return perim;
}

double min(Point points[], int n)
{
    double min_cover = INFINITY;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double d = dist(points[i], points[j]);
            if (d < min_cover)
            {
                min_cover = d;
            }
        }
    }
    return min_cover;
}

// Divide and Conquer algorithm
double divide_and_conquer(Point points[], int n)
{
    if (n <= 3)
    {
        return min(points, n);
    }
    int mid = n / 2;
    Point mid_point = points[mid];

    double d_left = divide_and_conquer(points, mid);
    double d_right = divide_and_conquer(points + mid, n - mid);
    double d_min = fmin(d_left, d_right);

    // Merge
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (fabs(points[i].x - mid_point.x) < d_min)
        {
            strip[j] = points[i];
            j++;
        }
    }

    // Find closest pair in strip
    for (int i = 0; i < j; i++)
    {
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y) < d_min; k++)
        {
            double d = dist(strip[i], strip[k]);
            if (d < d_min)
            {
                d_min = d;
            }
        }
    }
    return d_min;
}

int main()
{
    Point points[MAX_POINTS];
    srand(time(NULL));
    // Generate random points
    FILE *filePointer;
    filePointer = fopen("file.txt", "w");

    for (int i = 0; i < MAX_POINTS; i++)
    {
        points[i].x = rand() % 100;
        points[i].y = rand() % 100;
        fprintf(filePointer, "%d %d\n", points[i].x, points[i].y);
    }
    fclose(filePointer);

    printf("Points making the hull are:-\n");
    // Brute-force algorithm
    clock_t start, end;
    start = clock();
    bruteforce(points);
    end = clock();
    double time_bf = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nBrute-force algorithm:\nTime taken: %lf seconds\n\n",
           time_bf);

    // Graham's Scan algorithm
    clock_t start1, end1;
    start1 = clock();
    double min_cover_gs = graham_scan(points, MAX_POINTS);
    end1 = clock();
    double time_gs = ((double)(end1 - start1)) / CLOCKS_PER_SEC;
    printf("Graham's Scan algorithm:\nTime taken: %lf seconds\n\n", time_gs);

    // Divide and Conquer algorithm
    clock_t start2, end2;
    start2 = clock();
    double min_cover_dc = divide_and_conquer(points, MAX_POINTS);
    end2 = clock();
    double time_dc = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
    printf("Divide and Conquer algorithm:\nTime taken: %lf seconds\n\n", time_dc);

    return 0;
}
```
