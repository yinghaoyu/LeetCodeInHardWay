#include <algorithm>
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
  class Info
  {
   public:
    int maxSum;          // 最大值不经过当前节点
    int maxSumFromHead;  // 最大值经过当前节点
    Info(int path, int head)
    {
      maxSum = path;
      maxSumFromHead = head;
    }
  };

  Info process(TreeNode *x)
  {
    if (x == nullptr)
    {
      return Info(INT32_MIN, INT32_MIN);
    }
    Info leftInfo = process(x->left);
    Info rightInfo = process(x->right);
    int p1 = leftInfo.maxSum;
    int p2 = rightInfo.maxSum;
    int p3 = x->val;
    int p4 = x->val + leftInfo.maxSumFromHead;
    int p5 = x->val + rightInfo.maxSumFromHead;
    int p6 = x->val + leftInfo.maxSumFromHead + rightInfo.maxSumFromHead;
    int maxSum = std::max(std::max(p1, p2), std::max(std::max(p3, p4), std::max(p5, p6)));
    int maxSumFromHead = std::max(p3, std::max(p4, p5));
    return Info(maxSum, maxSumFromHead);
  }

  int maxPathSum(TreeNode *root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    return process(root).maxSum;
  }
};

void testMaxPathSum()
{
  Solution s;
  TreeNode *x3 = new TreeNode(3);
  TreeNode *x2 = new TreeNode(2);
  TreeNode *x1 = new TreeNode(1, x2, x3);

  TreeNode *y5 = new TreeNode(7);
  TreeNode *y4 = new TreeNode(15);
  TreeNode *y3 = new TreeNode(20, y4, y5);
  TreeNode *y2 = new TreeNode(9);
  TreeNode *y1 = new TreeNode(-10, y2, y3);
  EXPECT_EQ_INT(6, s.maxPathSum(x1));
  EXPECT_EQ_INT(42, s.maxPathSum(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxPathSum();
  return 0;
}
