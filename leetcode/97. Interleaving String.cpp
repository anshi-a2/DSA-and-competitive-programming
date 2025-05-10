// PROBLEM :


Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where s and t are divided into n and m substrings respectively, such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.


Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Explanation: One way to obtain s3 is:
Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
Since s3 can be obtained by interleaving s1 and s2, we return true.
  
Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
Explanation: Notice how it is impossible to interleave s2 with any other string to obtain s3.
  
Example 3:

Input: s1 = "", s2 = "", s3 = ""
Output: true



// SOLUTION 01 (using 2D DP) :


class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length();
        int n = s2.length();
        int l = s3.length();

        // If the lengths don't add up, it's not a valid interleaving
        if (m + n != l) return false;

        // dp[i][j] = true if s3[0..i+j-1] is formed by interleaving s1[0..i-1] and s2[0..j-1]
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true; // Empty strings interleave to form an empty string

        // Initialize the first column (using only s1)
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }

        // Initialize the first row (using only s2)
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
        }

        // Fill the rest of the dp table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // Two cases:
                // 1. The current char of s3 came from s1 (if previous in s1 matched)
                // 2. The current char of s3 came from s2 (if previous in s2 matched)
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                           (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }

        // The answer is whether the entire s3 can be formed from s1 and s2
        return dp[m][n];
    }
};


// SOLUTION 02 (using 1D DP) :


class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length(), l = s3.length();
        
        // If the combined lengths of s1 and s2 don't match s3, return false
        if (m + n != l) return false;
        
        // Always make s1 the longer string to use less space in the 1D dp array
        if (m < n) return isInterleave(s2, s1, s3);

        // Initialize a 1D DP array of size n + 1
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // Base case: empty s1 and s2 can form empty s3

        // Fill the first row (when s1 is empty)
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] && s2[j - 1] == s3[j - 1];
        }

        // Iterate through all characters of s1
        for (int i = 1; i <= m; ++i) {
            // Update the first column for the current row
            dp[0] = dp[0] && s1[i - 1] == s3[i - 1];
            
            // Update the rest of the dp array for current i
            for (int j = 1; j <= n; ++j) {
                // dp[j] from the previous row represents using s1[i-1]
                // dp[j-1] represents using s2[j-1]
                dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                        (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }

        // The answer is whether the entire s3 can be formed
        return dp[n];
    }
};






