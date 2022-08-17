#include <iostream>

#include "UnitTest.h"

using namespace std;

class TreeNode
{
 public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Info
{
 public:
  int deep;
  int value;
  Info()
  {
    deep = 0;
    value = 0;
  }
  Info(int d, int v)
  {
    deep = d;
    value = v;
  }
};

class Solution
{
 public:
  Info process(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return Info(0, 0);
    }
    if (cur->left == nullptr && cur->right == nullptr)
    {
      return Info(1, cur->val);
    }
    Info l;
    Info r;
    if (cur->left != nullptr)
    {
      l = process(cur->left);
    }
    if (cur->right != nullptr)
    {
      r = process(cur->right);
    }
    int deep = std::max(l.deep, r.deep) + 1;
    int value = 0;
    if (l.deep == r.deep)
    {
      value = l.value + r.value;
    }
    else if (l.deep > r.deep)
    {
      value = l.value;
    }
    else
    {
      value = r.value;
    }
    return Info(deep, value);
  }
  int deepestLeavesSum(TreeNode *root) { return process(root).value; }
};

void testDeepestLeavesSum()
{
  Solution s;
  TreeNode *x8 = new TreeNode(8, nullptr, nullptr);
  TreeNode *x7 = new TreeNode(7, nullptr, nullptr);
  TreeNode *x6 = new TreeNode(6, nullptr, x8);
  TreeNode *x5 = new TreeNode(5, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(4, x7, nullptr);
  TreeNode *x3 = new TreeNode(3, nullptr, x6);
  TreeNode *x2 = new TreeNode(2, x4, x5);
  TreeNode *x1 = new TreeNode(1, x2, x3);
  EXPECT_EQ_INT(s.deepestLeavesSum(x1), 15);
  EXPECT_SUMMARY;
}

int main()
{
  testDeepestLeavesSum();
  return 0;
}
