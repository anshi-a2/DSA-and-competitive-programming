// PROBLEM :

Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 
Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
  
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).



// SOLUTION :


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int closestSum = nums[0] + nums[1] + nums[n - 1];
        int minDiff = abs(closestSum - target);

        for (int i = 0; i < n - 2; ++i) {
            // Optional: skip duplicate values
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                int diff = sum - target;

                // If exact match is found, return immediately
                if (diff == 0) return sum;

                // Update closest sum if this one is closer
                if (abs(diff) < minDiff) {
                    minDiff = abs(diff);
                    closestSum = sum;
                }

                // Move pointers based on comparison
                if (diff < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        return closestSum;
    }
};



