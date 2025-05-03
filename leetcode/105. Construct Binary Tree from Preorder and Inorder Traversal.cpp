// PROBLEM :


Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

Example 1:

Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
  
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]



// SOLUTION :


class Solution {

private:
    int preorderIndex;
    unordered_map<int, int> mapping;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        mapping.clear();
        for (int i = 0; i < inorder.size(); i++) {
            mapping[inorder[i]] = i;
        }

        preorderIndex = 0;
        return build(preorder, 0, inorder.size() - 1);
    }

private:
    TreeNode* build(vector<int>& preorder, int start, int end) {
        if (start > end) return nullptr;

        int rootVal = preorder[preorderIndex++];
        TreeNode* root = new TreeNode(rootVal);
        int mid = mapping[rootVal];

        root->left = build(preorder, start, mid - 1);
        root->right = build(preorder, mid + 1, end);

        return root;
    }    
};



