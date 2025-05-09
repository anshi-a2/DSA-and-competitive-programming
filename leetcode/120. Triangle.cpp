// PROBLEM :


Given a triangle array, return the minimum path sum from top to bottom.
For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
  
Example 2:

Input: triangle = [[-10]]
Output: -10


// SOLUTION :


class Solution {
public:
    // Returns the minimum path sum from top to bottom of the triangle
    int minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();

        // Start with the bottom row of the triangle as the initial memo
        // memo[i] will eventually hold the minimum path sum from triangle[0][0] to a position in row i
        vector<int> memo = triangle[row - 1];

        // Start from the second-to-last row and move upward
        for (int r = row - 2; r >= 0; r--) {
            for (int c = 0; c <= r; c++) {
                // For each element, choose the minimum path by going down or down-right in the triangle
                memo[c] = min(memo[c], memo[c + 1]) + triangle[r][c];
            }
        }

        // After processing, memo[0] contains the minimum path sum from top to bottom
        return memo[0];        
    }
};




