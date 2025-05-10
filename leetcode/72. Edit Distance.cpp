// PROBLEM :

Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
  
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')


// SOLUTION :


class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();

        // Create a 2D DP array where dp[i][j] represents the edit distance
        // between the first i characters of word1 and the first j characters of word2
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Initialize base cases:
        // dp[i][0] = i deletions needed to convert word1[0..i-1] to empty string
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }

        // dp[0][j] = j insertions needed to convert empty string to word2[0..j-1]
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // Fill the DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    // Characters match, no operation needed
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Choose the minimum cost among replace, delete, or insert
                    dp[i][j] = min({
                        dp[i - 1][j - 1], // Replace
                        dp[i - 1][j],     // Delete
                        dp[i][j - 1]      // Insert
                    }) + 1;
                }
            }
        }

        // The bottom-right cell contains the answer
        return dp[m][n];
    }
};



// SOLUTION 02 ( 0(n) space ) :


class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();

        // Always use the shorter word for the 1D DP array to save space
        if (n > m) return minDistance(word2, word1);

        // Initialize a 1D DP array for previous and current rows
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        // Base case: converting empty word1 to word2
        for (int j = 0; j <= n; ++j) {
            prev[j] = j;
        }

        // Fill DP rows one by one
        for (int i = 1; i <= m; ++i) {
            curr[0] = i; // Base case: converting word1[0..i-1] to empty string
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = prev[j - 1]; // No operation needed
                } else {
                    curr[j] = min({
                        prev[j - 1], // Replace
                        prev[j],     // Delete
                        curr[j - 1]  // Insert
                    }) + 1;
                }
            }
            swap(prev, curr); // Move current row to previous
        }

        return prev[n];
    }
};


