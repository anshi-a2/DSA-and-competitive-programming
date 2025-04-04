// PROBLEM :

Given two binary strings a and b, return their sum as a binary string.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"


//SOLUTION :

class Solution {
public:
    string addBinary(string a, string b) {
         string res;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;

    // Loop as long as there's something left to process
    while (i >= 0 || j >= 0 || carry) {
        if (i >= 0) carry += a[i--] - '0';  // Add bit from 'a'
        if (j >= 0) carry += b[j--] - '0';  // Add bit from 'b'

        res.push_back(carry % 2 + '0');  // Append the current result bit
        carry /= 2;  // Update carry for the next iteration
    }

    // No need to reverse the string since we append from right to left
    return {res.rbegin(), res.rend()};
    }
};
