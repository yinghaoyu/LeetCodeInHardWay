#include <iostream>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
 private:
  class Info
  {
   public:
    bool findA;
    bool findB;
    TreeNode* ans;

    Info(bool fa, bool fb, TreeNode* t)
    {
      this->findA = fa;
      this->findB = fb;
      this->ans = t;
    }
  };

 public:
  Info f(TreeNode* cur, TreeNode* p, TreeNode* q)
  {
    if (cur == NULL)
    {
      return Info(false, false, NULL);
    }
    Info left = f(cur->left, p, q);
    Info right = f(cur->right, p, q);
    bool findA = cur->val == p->val || left.findA || right.findA;
    bool findB = cur->val == q->val || left.findB || right.findB;
    TreeNode* ans = NULL;
    if (left.ans != NULL)
    {
      ans = left.ans;
    }
    else if (right.ans != NULL)
    {
      ans = right.ans;
    }
    else
    {
      if (findA && findB)
      {
        ans = cur;
      }
    }
    return Info(findA, findB, ans);
  }

  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
  {
    return f(root, p, q).ans;
  }

  // 简化版
  TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q)
  {
    if (root == nullptr)
    {
      return nullptr;
    }
    if (root == p || root == q)
    {
      return root;
    }
    TreeNode* left = dfs(root->left, p, q);
    TreeNode* right = dfs(root->right, p, q);
    if (left && right)
    {
      return root;
    }
    return left == nullptr ? right : left;
  }
};
