// PROBLEM :

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.


Example 1:

Input: nums = [2,2,1]
Output: 1

Example 2:

Input: nums = [4,1,2,1,2]
Output: 4


  // SOLUTION :

class Solution {
public:
    int singleNumber(vector<int>& nums) { 
       int ans=0;
	   for(auto x:nums)
	   ans^=x;
	   return ans;
    }
};

//note : x ^ x = 0 (XOR-ing a number with itself results in zero)  ,   x ^ 0 = x (XOR-ing a number with zero results in the number itself)
