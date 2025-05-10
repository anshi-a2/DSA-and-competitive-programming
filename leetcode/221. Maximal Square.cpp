// PROBLEM :

Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example 1:

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4
  
Example 2:

Input: matrix = [["0","1"],["1","0"]]
Output: 1
  
Example 3:

Input: matrix = [["0"]]
Output: 0


// SOLUTION :


class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        // If the matrix is empty or has no columns, return 0
        if (matrix.empty() || matrix[0].empty()) return 0;

        int m = matrix.size();
        int n = matrix[0].size();

        // Create a DP table with extra row and column (size m+1 x n+1)
        // Initialized to 0 to handle boundary conditions easily
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxSide = 0; // To keep track of the largest square's side length

        // Start from (1,1) because dp is 1-based to simplify boundaries
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // Only process if the current cell in original matrix is '1'
                if (matrix[i - 1][j - 1] == '1') {
                    // dp[i][j] = 1 + minimum of top, left, and top-left neighbors
                    dp[i][j] = min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
                    // Update the maximum square side length
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        // Return the area of the largest square found
        return maxSide * maxSide;
    }
};


