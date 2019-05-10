/*
 * @lc app=leetcode id=572 lang=cpp
 *
 * [572] Subtree of Another Tree
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        if (s == nullptr) {
            return t == nullptr;
        }

        if (t == nullptr) {
            return false;
        }

        if (s->val != t->val) {
            return false;
        }

        return isSameTree(s->right, t->right) && isSameTree(s->left, t->left);
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == nullptr || t == nullptr) {
            return false;
        }

        if (isSameTree(s, t)) {
            return true;
        }

        if (isSubtree(s->left, t)) {
            return true;
        }

        return isSubtree(s->right, t);
    }
};

