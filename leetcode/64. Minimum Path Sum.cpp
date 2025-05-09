// PROBLEM :

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:

Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:

Input: grid = [[1,2,3],[4,5,6]]
Output: 12


// SOLUTION (in place DP):


class Solution {
public:
    // Returns the minimum path sum from top-left to bottom-right in a grid
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();        // Number of rows
        int n = grid[0].size();     // Number of columns

        // Pre-fill the first column: can only come from above
        for (int i = 1; i < m; i++) {
            grid[i][0] += grid[i - 1][0];
        }

        // Pre-fill the first row: can only come from the left
        for (int j = 1; j < n; j++) {
            grid[0][j] += grid[0][j - 1];
        }

        // Fill the rest of the grid using DP:
        // At each cell, choose the minimum path sum from the top or left neighbor
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            }
        }

        // The bottom-right cell contains the minimum path sum
        return grid[m - 1][n - 1];
    }
};


