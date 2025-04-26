// PROBLEM :


Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
  
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]


// SOLUTION (BRUTE FORCE) :


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int size=nums.size();
        int prod=1;
        int check=0;
        for(int i=0;i<size;i++){
            if(nums[i]!=0){
                 prod=nums[i]*prod;
            }else{
                check++;
            }
           
        }
        vector<int>ans;

        for(int i=0;i<size;i++){
            if(nums[i]==0&&check==1){
              nums[i]=prod;
            }else if(check==0){

               nums[i]=prod/nums[i];
            }else if(check!=0){
                nums[i]=0;
            }
        }
        return nums;
    }
};



// SOLUTION 02 (No division, with minimal check):

class Solution {
public:
    vector<int> productExceptSelf(const vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);

        int prefix = 1;
        for (int i = 0; i < n; ++i) {
            ans[i] = prefix;
            prefix *= nums[i];
        }
        
        int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            ans[i] *= suffix;
            suffix *= nums[i];
        }
        
        return ans;
    }
};

