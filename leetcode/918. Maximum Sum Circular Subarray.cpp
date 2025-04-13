// PROBLEM :

Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.
A circular array means the end of the array connects to the beginning of the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].
A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.

Example 1:

Input: nums = [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3.

Example 2:

Input: nums = [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.



// SOLUTION :

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        
        // Initialize variables for max sum, min sum, and current sums
        int maxSum = nums[0], minSum = nums[0], curMax = 0, curMin = 0;
        int totalSum = 0;

        // Iterate over the array to calculate max sum, min sum and total sum
        for (int num : nums) {
            curMax = max(curMax + num, num);  // Kadane's for max sum
            maxSum = max(maxSum, curMax);
            
            curMin = min(curMin + num, num);  // Kadane's for min sum
            minSum = min(minSum, curMin);
            
            totalSum += num;  // Accumulate total sum of the array
        }

        // Handle the edge case when all elements are negative
        // If maxSum is less than 0, no need to consider circular subarray
        if (maxSum > 0) {
            return max(maxSum, totalSum - minSum);  // Maximum of regular max sum or circular max sum
        } else {
            return maxSum;  // All elements are negative, return the regular max sum
        }
    }
};
