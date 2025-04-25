// PROBLEM :



Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
  
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
  
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0


// SOLUTION :


class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minLen = numeric_limits<int>::max();
        int left = 0;
        int curSum = 0;

        for (int right = 0; right < nums.size(); right++) {
            curSum += nums[right];

            while (curSum >= target) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                }
                curSum -= nums[left];
                left++;
            }
        }

        return minLen != numeric_limits<int>::max() ? minLen : 0; 
    }
};
