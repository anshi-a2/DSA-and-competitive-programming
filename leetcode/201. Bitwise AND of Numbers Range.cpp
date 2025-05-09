// PROBLEM :

Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: left = 5, right = 7
Output: 4
  
Example 2:

Input: left = 0, right = 0
Output: 0
  
Example 3:

Input: left = 1, right = 2147483647
Output: 0


// SOLUTION :

class Solution {
public:
    // This function returns the bitwise AND of all numbers in the range [left, right]
    int rangeBitwiseAnd(int left, int right) {
        int cnt = 0;

        // The idea is to find the common bit prefix of left and right.
        // As long as left and right are different, shift both right (>> 1)
        // and count how many shifts we did.
        while (left != right) {
            left >>= 1;   // Right shift left by 1 (divide by 2)
            right >>= 1;  // Right shift right by 1 (divide by 2)
            cnt++;        // Count how many times we shift
        }

        // When left == right, we've found the common prefix.
        // Shift it back to the left cnt times to get the result.
        return (left << cnt); // Reconstruct the result by left-shifting
    }
};



