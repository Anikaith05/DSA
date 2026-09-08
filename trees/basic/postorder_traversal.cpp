#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

 class Solution {
public:
    void traverse(TreeNode*root,vector<int>&order){
        if(root==nullptr){
            return;
        }
        traverse(root->left,order);
        traverse(root->right,order);
        order.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>order;
        traverse(root,order);
        return order;
    }
};