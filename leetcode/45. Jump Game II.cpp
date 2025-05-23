// PROBLEM :

You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].

Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at nums[i], you can jump to any nums[i + j] where:

0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n - 1].

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: nums = [2,3,0,1,4]
Output: 2



// SOLUTION :



class Solution {
public:
    int jump(vector<int>& nums) {
        //till what index you can go withput jump
        int maxR = nums[0];
        int jumps=1;
        //no of steps you can go to reach max index
        int steps = nums[0];
        int n = nums.size();
        if(n==1)return 0;
        else if(nums[0]==0)return -1;
        else {
            for(int i=1;i<n;i++) {
                if(i==n-1)return jumps;
                maxR = max(maxR, nums[i]+i);
                steps--;
                if(steps==0){
                    jumps++;
                    if(i>=maxR)return -1;
                    steps=maxR-i;
                }
            }
        }
        return -1;

    }
};


