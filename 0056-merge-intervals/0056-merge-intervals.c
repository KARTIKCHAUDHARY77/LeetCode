#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int *x = *(int **)a;
    int *y = *(int **)b;

    return x[0] - y[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes)
{
    qsort(intervals, intervalsSize, sizeof(int *), compare);
    int k = 0;
    for (int i = 0; i < intervalsSize; i++)
    {
        if (k == 0 || intervals[k - 1][1] < intervals[i][0])
        {
            intervals[k][0] = intervals[i][0];
            intervals[k][1] = intervals[i][1];
            k++;
        }
        else
        {
            if (intervals[i][1] > intervals[k - 1][1])
            {
                intervals[k - 1][1] = intervals[i][1];
            }
        }
    }
    *returnSize = k;
    *returnColumnSizes = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++)
    {
        (*returnColumnSizes)[i] = 2;
    }
    return intervals;
}