// PROBLEM :


Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

Example 1:

Input: nums = [3,2,3]
Output: 3
  
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2


// SOLUTION :


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> hash;
        int res = 0;
        int majority = 0;

        for (int n : nums) {
            hash[n] = 1 + hash[n];
            if (hash[n] > majority) {
                res = n;
                majority = hash[n];
            }
        }

        return res; 
    }
};
