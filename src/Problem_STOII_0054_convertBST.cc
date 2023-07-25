#include <iostream>
#include <vector>

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

// seem as leetcode 0538 1038
// https://leetcode-cn.com/problems/convert-bst-to-greater-tree/
// https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/
// see at Problem_0538_convertBST.cc Problem_1038_bstToGst.cc
// 反向 Morris 遍历
class Solution
{
 public:
  TreeNode *convertBST(TreeNode *root)
  {
    TreeNode *cur = root;
    TreeNode *mostLeft = nullptr;
    int sum = 0;
    while (cur != nullptr)
    {
      mostLeft = cur->right;
      if (mostLeft)
      {
        while (mostLeft->left != nullptr && mostLeft->left != cur)
        {
          mostLeft = mostLeft->left;
        }
        if (mostLeft->left == nullptr)
        {
          mostLeft->left = cur;
          cur = cur->right;
          continue;
        }
        else
        {
          mostLeft->left = nullptr;
        }
      }
      sum += cur->val;
      cur->val = sum;
      cur = cur->left;
    }
    return root;
  }
};
