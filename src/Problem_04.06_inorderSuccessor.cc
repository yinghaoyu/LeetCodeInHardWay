#include <iostream>

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
 public:
  // Morris
  TreeNode* inorderSuccessor1(TreeNode* root, TreeNode* p)
  {
    TreeNode* cur = root;
    TreeNode* pre = nullptr;
    TreeNode* ans = nullptr;
    TreeNode* mostRight = nullptr;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight != nullptr)
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          mostRight->right = cur;
          cur = cur->left;
          continue;
        }
        else
        {
          mostRight->right = nullptr;
        }
      }
      if (pre == p && ans == nullptr)
      {
        ans = cur;
      }
      pre = cur;
      cur = cur->right;
    }
    return ans;
  }

  TreeNode* inorderSuccessor2(TreeNode* root, TreeNode* p)
  {
    if (root == nullptr)
    {
      return nullptr;
    }
    // 当前节点值小于等于目标值，那么当前目标值的后继者必然在右子树
    if (root->val <= p->val)
    {
      return inorderSuccessor2(root->right, p);
    }
    // 否则结果有可能是当前节点，或者在当前节点的左子树中
    // 那么先去左子树找一下试试，找不到的话返回当前节点即是结果
    TreeNode* node = inorderSuccessor2(root->right, p);
    return node == nullptr ? root : node;
  }
};
