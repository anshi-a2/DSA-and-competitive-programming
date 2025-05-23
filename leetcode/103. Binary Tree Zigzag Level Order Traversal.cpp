// PROBLEM :


Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
  
Example 2:

Input: root = [1]
Output: [[1]]
  
Example 3:

Input: root = []
Output: []



// SOLUTION :



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root==NULL) return ans;
        queue<TreeNode*> q;
        q.push(root);
        int cnt = 1;
        while(!q.empty()){
            vector<int> temp;
            int n = q.size();
            for(int i = 0 ;i<n;i++){
                TreeNode* node = q.front();
                q.pop();
                temp.push_back(node->val); 
                if(node->left!=NULL)q.push(node->left);
                if(node->right!=NULL)q.push(node->right); 
            }
            if(cnt%2==0) reverse(temp.begin() ,temp.end());
            ans.push_back(temp);
            cnt++;
        }
        return ans;
    }
};




