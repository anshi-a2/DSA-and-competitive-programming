// PROBLEM :

Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.
You must not use any built-in exponent function or operator.
For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.

Example 1:
Input: x = 4
Output: 2
Explanation: The square root of 4 is 2, so we return 2.


// SOLUTION :

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0 || x == 1) return x;  // Base cases
        
        int l = 1, r = x;
        while (l <= r) {
            int m = l + (r - l) / 2;  // Prevent overflow, equivalent to (l + r) / 2
            if (m > x / m) {
                r = m - 1;  // Reduce the upper bound
            } else if (m < x / m) {
                l = m + 1;  // Increase the lower bound
            } else {
                return m;  // Exact match found
            }
        }
        return r;  // If not an exact match, return the floor of sqrt(x)
    }
};
