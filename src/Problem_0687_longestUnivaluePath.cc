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

class Solution
{
 public:
  int ans = 0;
  int process1(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    int left = process1(cur->left);
    int right = process1(cur->right);
    int p1 = 0, p2 = 0;
    if (cur->left != nullptr && cur->left->val == cur->val)
    {
      p1 = left + 1;
    }

    if (cur->right != nullptr && cur->right->val == cur->val)
    {
      p2 = right + 1;
    }

    ans = std::max(ans, p1 + p2);
    return std::max(p1, p2);
  }

  int longestUnivaluePath1(TreeNode *root)
  {
    process1(root);
    return ans;
  }

  // 建立以x节点为头的树，返回两个信息
  class Info
  {
   public:
    // 在一条路径上：要求每个节点通过且只通过一遍
    int len;  // 路径必须从x出发且只能往下走的情况下，路径的最大距离
    int max;  // 路径不要求必须从x出发的情况下，整颗树的合法路径最大距离
    Info(int l, int m)
    {
      len = l;
      max = m;
    }
  };

  Info process2(TreeNode *x)
  {
    if (x == nullptr)
    {
      return Info(0, 0);
    }
    TreeNode *l = x->left;
    TreeNode *r = x->right;

    Info lInfo = process2(l);
    Info rInfo = process2(r);
    // 至少存在当前节点
    int len = 1;

    if (l != nullptr && l->val == x->val)
    {
      // 当前节点加入左孩子结构，那么节点数+1
      len = lInfo.len + 1;
    }
    if (r != nullptr && r->val == x->val)
    {
      // 当前节点加入右孩子结构，那么节点数+1
      len = std::max(len, rInfo.len + 1);
    }
    int max = std::max(std::max(lInfo.max, rInfo.max), len);
    if (l != nullptr && r != nullptr && l->val == x->val && r->val == x->val)
    {
      // 左孩子、右孩子、当前节点合并，节点数+1
      max = std::max(max, lInfo.len + rInfo.len + 1);
    }
    return Info(len, max);
  }

  int longestUnivaluePath2(TreeNode *root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    // 边的数量 = 节点数量 - 1
    return process2(root).max - 1;
  }
};

void testLongestUnivaluePath()
{
  Solution s;
  TreeNode *x6 = new TreeNode(5, nullptr, nullptr);
  TreeNode *x5 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(5, nullptr, x6);
  TreeNode *x2 = new TreeNode(4, x4, x5);
  TreeNode *x1 = new TreeNode(5, x2, x3);

  TreeNode *y6 = new TreeNode(5, nullptr, nullptr);
  TreeNode *y5 = new TreeNode(4, nullptr, nullptr);
  TreeNode *y4 = new TreeNode(4, nullptr, nullptr);
  TreeNode *y3 = new TreeNode(5, nullptr, y6);
  TreeNode *y2 = new TreeNode(4, y4, y5);
  TreeNode *y1 = new TreeNode(1, y2, y3);
  EXPECT_EQ_INT(2, s.longestUnivaluePath1(x1));
  EXPECT_EQ_INT(2, s.longestUnivaluePath1(y1));
  EXPECT_EQ_INT(2, s.longestUnivaluePath2(x1));
  EXPECT_EQ_INT(2, s.longestUnivaluePath2(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestUnivaluePath();
  return 0;
}
