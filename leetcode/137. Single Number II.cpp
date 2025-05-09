// PROBLEM :

Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:

Input: nums = [2,2,3,2]
Output: 3
  
Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99


// SOLUTION (BRUTE FORCE) :

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> m;
        
        for(auto x: nums){
            m[x]++;
        }

        for(auto x: m){
            if(x.second == 1){
                return x.first;
            }
        }
        
        return -1;
    }
};


// SOLUTION 02 (bit manipulation) :

class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        int ones = 0, twos = 0;
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }
};


// logic :

// ones Update:
// (ones ^ num): Adds the current number's bits to ones.
// & ~twos: Ensures that any bit present in twos (appearing twice) is removed from ones.
  
// twos Update:
// (twos ^ num): Adds the current number's bits to twos.
// & ~ones: Ensures that any bit present in ones (appearing once) is removed from twos.
  
// Bits that appear three times are cleared out from both ones and twos.



