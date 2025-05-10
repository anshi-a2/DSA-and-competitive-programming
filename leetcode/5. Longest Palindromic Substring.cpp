// PROBLEM :


Given a string s, return the longest palindromic substring in s.

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
  
Example 2:

Input: s = "cbbd"
Output: "bb"


// SOLUTION 01 (using two pointer 0(n^2) time and 0(1) space complexity):


class Solution {
public:
    // Returns the longest palindromic substring in the input string
    string longestPalindrome(string s) {
        if (s.empty()) {
            return "";
        }

        int start = 0, end = 0; // Indices of the longest palindrome found so far

        for (int i = 0; i < s.length(); i++) {
            // Check for odd-length palindrome centered at i
            int odd = expandAroundCenter(s, i, i);
            // Check for even-length palindrome centered between i and i+1
            int even = expandAroundCenter(s, i, i + 1);
            int max_len = max(odd, even); // Take the longer one

            // If we found a longer palindrome, update the start and end indices
            if (max_len > end - start) {
                start = i - (max_len - 1) / 2;
                end = i + max_len / 2;
            }
        }

        // Extract and return the longest palindrome substring
        return s.substr(start, end - start + 1);        
    }

private:
    // Expands around the given center and returns the length of the palindrome
    int expandAroundCenter(string s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;  // Expand to the left
            right++; // Expand to the right
        }
        // Length of the palindrome is right - left - 1
        return right - left - 1;
    }    
};


// SOLUTION 02 (Manacher’s Algorithm – Time: O(n), Space: O(n)) : can later check 








