#include <iostream>

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Morris
class Solution
{
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p)
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
};
