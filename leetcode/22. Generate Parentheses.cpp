// PROBLEM :


Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
  
Example 2:

Input: n = 1
Output: ["()"]


// SOLUTION :


class Solution {
public:
    void helper(vector<string> &ans, int oc, int cc,int n, string s){
        if(oc==n && cc==n){
            ans.push_back(s);
            return;
        }
        if(oc<n){
            helper(ans, oc+1, cc, n, s+"(");
        }
        if(cc<oc){
            helper(ans, oc, cc+1, n, s+")");
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        int oc=0;
        int cc=0;
        helper(ans, oc, cc, n, "");
        return ans;
    }
};



