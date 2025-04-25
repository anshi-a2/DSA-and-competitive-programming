// PROBLEM :

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
  
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]



// SOLUTION (BRUTE FORCE):


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        vector<int> rotated(n);

        for (int i = 0; i < n; i++) {
            rotated[(i + k) % n] = nums[i];
        }

        for (int i = 0; i < n; i++) {
            nums[i] = rotated[i];
        }        
    }
};



// SOLUTION 02 ; (IN PLACE ROTATION):



class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;  // Handle cases where k is larger than n
        
        // Step 1: Reverse the entire array
        reverse(nums.begin(), nums.end());
        
        // Step 2: Reverse the first k elements
        reverse(nums.begin(), nums.begin() + k);
        
        // Step 3: Reverse the remaining n-k elements
        reverse(nums.begin() + k, nums.end());
    }
};
