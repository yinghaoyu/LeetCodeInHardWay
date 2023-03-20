#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
 public:
  void flatten1(TreeNode *root)
  {
    TreeNode *cur = root;
    TreeNode *pre = nullptr;
    TreeNode *mostRight = nullptr;
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
          // 第一次遍历
          if (pre != nullptr)
          {
            // 因为是中序遍历，左孩子遍历完，left指针就不会用了，因此可以先用left串起来
            pre->left = cur;
          }
          pre = cur;
          cur = cur->left;
          continue;
        }
        else
        {
          // 忽视第二次遍历
          mostRight->right = nullptr;
        }
      }
      else
      {
        // 没有右孩子的节点只会遍历一次
        if (pre != nullptr)
        {
          pre->left = cur;
        }
        pre = cur;
      }
      cur = cur->right;
    }
    cur = root;
    TreeNode *next = nullptr;
    while (cur != nullptr)
    {
      // 再把left指针调整为right，left置空
      next = cur->left;
      cur->left = nullptr;
      cur->right = next;
      cur = next;
    }
  }

  // 递归
  TreeNode *last = nullptr;
  void flatten2(TreeNode *root)
  {
    if (root == nullptr)
    {
      return;
    }
    // 注意这里要先递归right
    flatten2(root->right);
    flatten2(root->left);
    root->right = last;
    root->left = nullptr;
    last = root;
  }
};
