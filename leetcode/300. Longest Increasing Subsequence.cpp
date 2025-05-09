// PROBLEM :


Given an integer array nums, return the length of the longest strictly increasing subsequence.

Example 1:

Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:

Input: nums = [0,1,0,3,2,3]
Output: 4
  
Example 3:

Input: nums = [7,7,7,7,7,7,7]
Output: 1



// SOLUTION :

// (This is an implementation of Patience Sorting technique)

class Solution {
public:
    // Returns the length of the Longest Increasing Subsequence in nums
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res; // res[i] will be the smallest possible tail of an increasing subsequence of length i+1

        for (int n : nums) {
            // If n is larger than the last element in res, it can extend the current longest subsequence
            if (res.empty() || res.back() < n) {
                res.push_back(n);
            } else {
                // Otherwise, find the first element in res >= n and replace it
                // This keeps res valid but with smaller elements to allow longer subsequences later
                int idx = binarySearch(res, n);
                res[idx] = n;
            }
        }

        // The length of res represents the length of the longest increasing subsequence
        return res.size();        
    }

private:
    // Custom binary search to find the first index in arr where arr[i] >= target
    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (arr[mid] == target) {
                return mid; // Exact match
            } else if (arr[mid] > target) {
                right = mid - 1; // Search left half
            } else {
                left = mid + 1; // Search right half
            }
        }

        return left; // Position to replace or insert
    }    
};



