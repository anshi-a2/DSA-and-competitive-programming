// PROBLEM :

Given an integer n, return the number of trailing zeroes in n!.
Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.

Example 1:
Input: n = 3
Output: 0
Explanation: 3! = 6, no trailing zero.
  
Example 2:
Input: n = 5
Output: 1
Explanation: 5! = 120, one trailing zero.
  
Example 3:
Input: n = 0
Output: 0


// SOLUTION :

class Solution {
public:
    int trailingZeroes(int n) {
        int cnt = 0;

        while (n >= 5) {
            n /= 5;        // Divide n by 5
            cnt += n;      // Add the quotient (i.e., number of multiples of 5)
        }

        return cnt; // Return the count of trailing zeroes
    }
};
