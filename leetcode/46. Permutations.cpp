// PROBLEM :


Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
  
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
  
Example 3:

Input: nums = [1]
Output: [[1]]



// SOLUTION :

class Solution {
public:
    // Function to return all possible permutations of the input vector 'nums'
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;  // Result vector to store all permutations

        // Base case: if only one number is present, return it as the only permutation
        if (nums.size() == 1) {
            res.push_back(nums);  // Directly push the single-element vector
            return res;
        }

        // Loop through each element in nums
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];  // Choose the current element as the first element of the permutation

            // Create a new vector that excludes the current element
            vector<int> remainingNums;
            for (int j = 0; j < nums.size(); j++) {
                if (j != i) {
                    remainingNums.push_back(nums[j]);  // Add all elements except nums[i]
                }
            }

            // Recursively generate permutations of the remaining elements
            vector<vector<int>> perms = permute(remainingNums);

            // Add the chosen element 'n' at the beginning of each generated permutation
            for (vector<int> p : perms) {
                p.insert(p.begin(), n);  // Insert n at the front
                res.push_back(p);        // Add this new permutation to the result
            }
        }

        return res;  // Return all accumulated permutations
    }
};


// SOLUTION 02 (In place permutaion without copying) :


class Solution {
public:
    // Main function to generate all permutations of the input vector
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;  // Stores all permutations
        backtrack(nums, 0, res);  // Start backtracking from index 0
        return res;
    }

private:
    // Helper function for backtracking
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& res) {
        if (start == nums.size()) {
            res.push_back(nums);  // Add a complete permutation to the result
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            swap(nums[start], nums[i]);           // Choose: fix the ith number at current position
            backtrack(nums, start + 1, res);      // Explore: recurse with the next position
            swap(nums[start], nums[i]);           // Unchoose: backtrack to original state
        }
    }
};





 
