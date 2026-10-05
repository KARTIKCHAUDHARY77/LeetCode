int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes)
{
    // Step 1: Sort intervals according to starting value
    for (int i = 0; i < intervalsSize - 1; i++)
    {
        for (int j = 0; j < intervalsSize - i - 1; j++)
        {
            if (intervals[j][0] > intervals[j + 1][0])
            {
                // Swap start
                int temp = intervals[j][0];
                intervals[j][0] = intervals[j + 1][0];
                intervals[j + 1][0] = temp;

                // Swap end
                temp = intervals[j][1];
                intervals[j][1] = intervals[j + 1][1];
                intervals[j + 1][1] = temp;
            }
        }
    }

    // Step 2: Allocate memory for answer
    int** result = malloc(intervalsSize * sizeof(int*));

    for (int i = 0; i < intervalsSize; i++)
    {
        result[i] = malloc(2 * sizeof(int));
    }

    int k = 0;

    // Step 3: Merge intervals
    for (int i = 0; i < intervalsSize; i++)
    {
        // If result is empty OR intervals don't overlap
        if (k == 0 || result[k - 1][1] < intervals[i][0])
        {
            result[k][0] = intervals[i][0];
            result[k][1] = intervals[i][1];

            k++;
        }
        else
        {
            // Overlapping intervals
            if (intervals[i][1] > result[k - 1][1])
            {
                result[k - 1][1] = intervals[i][1];
            }
        }
    }

    // Step 4: Tell LeetCode how many intervals we returned
    *returnSize = k;

    // Step 5: Tell LeetCode each row has 2 elements
    *returnColumnSizes = malloc(k * sizeof(int));

    for (int i = 0; i < k; i++)
    {
        (*returnColumnSizes)[i] = 2;
    }

    return result;
}