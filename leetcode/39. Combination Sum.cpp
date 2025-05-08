// PROBLEM :


Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
  
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
  
Example 3:

Input: candidates = [2], target = 1
Output: []



// SOLUTION :


class Solution {
public:
    // Entry function to find all combinations that sum up to the target
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;  // Stores all valid combinations
        vector<int> comb;         // Current combination being constructed
        makeCombination(candidates, target, 0, comb, 0, res);
        return res;
    }

private:
    // Recursive helper function to build combinations
    void makeCombination(vector<int>& candidates, int target, int idx, vector<int>& comb, int total, vector<vector<int>>& res) {
        // Base case: if total equals target, add a copy of comb to result
        if (total == target) {
            res.push_back(comb);
            return;
        }

        // If total exceeds target or we've used all candidates, backtrack
        if (total > target || idx >= candidates.size()) {
            return;
        }

        // Include the current candidate (can be used multiple times)
        comb.push_back(candidates[idx]);
        makeCombination(candidates, target, idx, comb, total + candidates[idx], res);
        comb.pop_back();  // Backtrack: remove last element

        // Skip the current candidate and move to the next
        makeCombination(candidates, target, idx + 1, comb, total, res);
    }
};




