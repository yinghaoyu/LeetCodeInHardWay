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

// seem as leetcode 0124
// https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/
// see at Problem_0124_maxPathSum.cc
class Solution
{
 private:
  class Info
  {
   public:
    Info(int m, int mfh)
    {
      maxSum = m;
      maxSumFromHead = mfh;
    }

    int maxSum;
    int maxSumFromHead;
  };

 public:
  Info dfs(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return Info(-1000, -1000);
    }
    Info left = dfs(cur->left);
    Info right = dfs(cur->right);
    int p1 = left.maxSum;
    int p2 = right.maxSum;
    int p3 = cur->val;
    int p4 = cur->val + left.maxSumFromHead;
    int p5 = cur->val + right.maxSumFromHead;
    int p6 = cur->val + left.maxSumFromHead + right.maxSumFromHead;
    // p1 p2 p6不能向上递归，p1 p2会使链断开，p6 会使链分叉
    int maxSum = std::max(std::max(p1, p2), std::max(std::max(p3, p4), std::max(p5, p6)));
    // p3 p4 p5能向上递归
    int maxSumFromHead = std::max(p3, std::max(p4, p5));
    return Info(maxSum, maxSumFromHead);
  }

  int maxPathSum(TreeNode *root) { return dfs(root).maxSum; }
};
