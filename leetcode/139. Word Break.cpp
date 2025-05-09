// PROBLEM :

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
  
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
  
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false


// SOLUTION :


class Solution {
public:
    // Determines if the string `s` can be segmented into a space-separated
    // sequence of one or more dictionary words.
    bool wordBreak(string s, vector<string>& wordDict) {
        // dp[i] will be true if the substring s[0...i-1] can be segmented
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true; // Empty string can always be segmented

        // Loop through all positions in the string
        for (int i = 1; i <= s.size(); i++) {
            // Check each word in the dictionary
            for (const string& w : wordDict) {
                int start = i - w.length(); // potential start index of the word
                // If the word fits, and the segment before it is valid
                if (start >= 0 && dp[start] && s.substr(start, w.length()) == w) {
                    dp[i] = true; // Mark dp[i] as reachable
                    break; // No need to check more words if dp[i] is true
                }
            }
        }

        // Return whether the entire string can be segmented
        return dp[s.size()];
    }
};



