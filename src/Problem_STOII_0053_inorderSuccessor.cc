#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// seem as leetcode 0285
// https://leetcode-cn.com/problems/inorder-successor-in-bst/
// see at Problem_0285_inorderSuccessor.cc
//
// Morris遍历
class Solution
{
 public:
  TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
  {
    TreeNode *cur = root;
    TreeNode *pre = nullptr;
    TreeNode *ans = nullptr;
    TreeNode *mostRight = nullptr;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight)
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
      if (ans == nullptr && pre == p)
      {
        ans = cur;
      }
      else
      {
        pre = cur;
      }
      cur = cur->right;
    }
    return ans;
  }
};
