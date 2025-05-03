// PROBLEM :


Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Example 1:

Input: p = [1,2,3], q = [1,2,3]
Output: true
  
Example 2:

Input: p = [1,2], q = [1,null,2]
Output: false



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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        
        if (p && q && p->val == q->val) {
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
        
        return false;        
    }
};


//  SOLUTION 02 (STACK VERFLOW SOLUTION) :



class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<pair<TreeNode*, TreeNode*>> qnodes;
        qnodes.push({p, q});
        
        while (!qnodes.empty()) {
            auto [node1, node2] = qnodes.front();
            qnodes.pop();
            
            if (!node1 && !node2) continue;
            if (!node1 || !node2) return false;
            if (node1->val != node2->val) return false;
            
            qnodes.push({node1->left, node2->left});
            qnodes.push({node1->right, node2->right});
        }
        
        return true;
    }
};






