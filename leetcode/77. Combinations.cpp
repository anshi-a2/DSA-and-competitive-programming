// PROBLEM :


Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].

You may return the answer in any order.

Example 1:

Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
  
Example 2:

Input: n = 1, k = 1
Output: [[1]]
Explanation: There is 1 choose 1 = 1 total combination.



// SOLUTION :


class Solution {
public:
    // Generates all possible combinations of k numbers out of the range [1, n]
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;   // To store all valid combinations
        vector<int> comb;          // Temporary combination during recursion

        // Start backtracking from number 1
        backtrack(1, comb, res, n, k);

        return res;        
    }

private:
    // Recursive backtracking function
    void backtrack(int start, vector<int>& comb, vector<vector<int>>& res, int n, int k) {
        // Base case: if the combination has k elements, add it to the result
        if (comb.size() == k) {
            res.push_back(comb);
            return;
        }

        // Iterate from 'start' to 'n' to build combinations in increasing order
        for (int num = start; num <= n; num++) {
            comb.push_back(num);                         // Choose current number
            backtrack(num + 1, comb, res, n, k);          // Recurse with next start
            comb.pop_back();                              // Backtrack: remove last number and try next
        }
    }    
};




