// PROBLEM :


Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

 
Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
  
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
  
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".


// SOLUTION :

  

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();

        // Create a 2D DP table initialized to false
        // dp[i][j] means whether s[0..i-1] matches p[0..j-1]
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));

        // Empty string matches empty pattern
        dp[0][0] = true;

        // Initialize first row (s is empty)
        // Handles patterns like a*, a*b*, a*b*c*, etc.
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                // '*' can eliminate the preceding character (p[j - 2])
                // So if dp[0][j - 2] is true, dp[0][j] should be true
                dp[0][j] = dp[0][j - 2];
            }
        }

        // Fill the rest of the DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {

                // If characters match or pattern has '.', which matches any character
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                    // Characters match, so take the previous result
                    dp[i][j] = dp[i - 1][j - 1];
                }

                // If pattern character is '*'
                else if (p[j - 1] == '*') {
                    // Case 1: Treat '*' and its preceding character as zero occurrence
                    dp[i][j] = dp[i][j - 2];

                    // Case 2: If the character before '*' matches current character in s
                    // or if it's a '.', then '*' can match this character as well
                    if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                        // Either zero occurrence (dp[i][j - 2]) or
                        // one or more occurrence (dp[i - 1][j])
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }

                // Else, dp[i][j] remains false by default
            }
        }

        // Return whether the full string matches the full pattern
        return dp[m][n];
    }
};




