// PROBLEM :

Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).

Example 1:

Input: n = 11
Output: 3

Explanation:
The input binary string 1011 has a total of three set bits.

Example 2:

Input: n = 128
Output: 1

Explanation:
The input binary string 10000000 has a total of one set bit.


// SOLUTION 01:

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            if ((n >> i) & 1) { // and operator gives the right most digit
                res += 1;
            }
        }
        return res;        
    }
};


// SOLUTION 02 Using Brian Kernighan's Algorithm :

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n) {
            n &= (n - 1);  // Drop the rightmost '1' bit
            res++;
        }
        return res;
    }
};

// note : if n is 10100, then n - 1 becomes 10011, and n & (n - 1) will result in 10000. This operation effectively removes one 1 bit from n in each iteration.

