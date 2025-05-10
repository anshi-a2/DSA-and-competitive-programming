// PROBLEM :


ou are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 * 109.


Example 1:

Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
  
Example 2:

Input: obstacleGrid = [[0,1],[0,0]]
Output: 1


// SOLUTION :


class Solution {
public:
    // Returns the number of unique paths from top-left to bottom-right in a grid with obstacles
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // Edge case: empty grid or obstacle at the start position
        if (obstacleGrid.empty() || obstacleGrid[0][0] == 1) {
            return 0;
        }

        int rows = obstacleGrid.size();
        int cols = obstacleGrid[0].size();

        // dp[c] stores the number of ways to reach cell (r, c) in the current row
        vector<int> dp(cols, 0);
        dp[0] = 1; // Start point has one path (if not blocked)

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (obstacleGrid[r][c] == 1) {
                    // If there's an obstacle at (r, c), no path can go through it
                    dp[c] = 0;
                } else if (c > 0) {
                    // Otherwise, add paths from the left (dp[c - 1])
                    dp[c] += dp[c - 1];
                }
                // If c == 0, only top contributes, which is already in dp[c]
            }
        }

        // The last element in dp holds the total number of paths to bottom-right
        return dp[cols - 1];        
    }
};




