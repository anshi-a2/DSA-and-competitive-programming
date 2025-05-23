// PROBLEM :


Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.

Example 1:

Input: root = [4,2,6,1,3]
Output: 1
  
Example 2:

Input: root = [1,0,48,null,null,12,49]
Output: 1


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
    void preorder(TreeNode* root, vector<int> & vec){
        if(root!= nullptr){
        preorder(root->left,vec);
        vec.push_back(root->val);
        preorder(root->right,vec);
        }
    }
    int getMinimumDifference(TreeNode* root) {
       vector<int> vec;
       preorder(root, vec);
       
       int diff{INT_MAX};
       for(int i=1;i<vec.size();i++){
            diff = min(diff,vec[i]-vec[i-1]);
       }
       return diff;
    }
};
