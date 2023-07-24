#include <iostream>
#include <queue>
#include <tuple>

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

// seem as leetcode 0129
// https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/
// Problem_0129_sumNumbers.cc
class Solution
{
 public:
  int sumNumbers(TreeNode *root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    int sum = 0;
    queue<tuple<TreeNode *, int>> q;
    q.push({root, root->val});
    while (!q.empty())
    {
      auto [node, num] = q.front();
      q.pop();
      if (node->left == nullptr && node->right == nullptr)
      {
        sum += num;
      }
      else
      {
        if (node->left != nullptr)
        {
          q.push({node->left, num * 10 + node->left->val});
        }
        if (node->right != nullptr)
        {
          q.push({node->right, num * 10 + node->right->val});
        }
      }
    }
    return sum;
  }
};
