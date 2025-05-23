// PROBLEM :

Given an integer array nums, find the subarray with the largest sum, and return its sum.

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
  
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.



// SOLUTION :


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int maxSum = nums[0], curMax = 0;

        for (int num : nums) {
            curMax = max(curMax + num, num);
            maxSum = max(maxSum, curMax);
        }

        return maxSum; 
    }
};
