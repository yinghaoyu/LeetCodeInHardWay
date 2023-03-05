#include <iostream>

#include "UnitTest.h"

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  TreeNode(int x, TreeNode *l, TreeNode *r)
  {
    val = x;
    left = l;
    right = r;
  }
};

class Solution
{
 private:
  class Info
  {
   public:
    TreeNode *ans;
    bool findO1;  // 左边有没有找到 o1 o2
    bool findO2;  // 右边有没有找到 o1 o2

    Info(TreeNode *node, bool f1, bool f2)
    {
      ans = node;
      findO1 = f1;
      findO2 = f2;
    }
  };

 public:
  Info process(TreeNode *x, TreeNode *o1, TreeNode *o2)
  {
    if (x == nullptr)
    {
      return Info(nullptr, false, false);
    }
    Info left = process(x->left, o1, o2);
    Info right = process(x->right, o1, o2);
    bool findO1 = x == o1 || left.findO1 || right.findO1;
    bool findO2 = x == o2 || left.findO2 || right.findO2;
    TreeNode *ans = nullptr;
    if (left.ans != nullptr)
    {
      ans = left.ans;
    }
    if (right.ans != nullptr)
    {
      ans = right.ans;
    }
    if (ans == nullptr)
    {
      // 左右子树都找到对应的节点，返回父节点
      if (findO1 && findO2)
      {
        ans = x;
      }
    }
    return Info(ans, findO1, findO2);
  }

  TreeNode *lowestCommonAncestor1(TreeNode *root, TreeNode *p, TreeNode *q) { return process(root, p, q).ans; }

  TreeNode *dfs(TreeNode *x, TreeNode *p, TreeNode *q)
  {
    if (x == nullptr || x == p || x == q)
    {
      return x;
    }
    TreeNode *left = dfs(x->left, p, q);
    TreeNode *right = dfs(x->right, p, q);
    if (left == nullptr)
    {
      return right;
    }
    if (right == nullptr)
    {
      return left;
    }
    return x;
  }

  TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q) { return dfs(root, p, q); }
};

void testLowestCommonAncestor()
{
  Solution s;
  TreeNode *r9 = new TreeNode(4, nullptr, nullptr);
  TreeNode *r8 = new TreeNode(7, nullptr, nullptr);
  TreeNode *r7 = new TreeNode(8, nullptr, nullptr);
  TreeNode *r6 = new TreeNode(0, nullptr, nullptr);
  TreeNode *r5 = new TreeNode(2, r8, r9);
  TreeNode *r4 = new TreeNode(6, nullptr, nullptr);
  TreeNode *r3 = new TreeNode(1, r6, r7);
  TreeNode *r2 = new TreeNode(5, r4, r5);
  TreeNode *r1 = new TreeNode(3, r2, r3);
  EXPECT_TRUE(r1 == s.lowestCommonAncestor1(r1, r2, r3));
  EXPECT_TRUE(r2 == s.lowestCommonAncestor1(r1, r2, r9));
  EXPECT_TRUE(r1 == s.lowestCommonAncestor2(r1, r2, r3));
  EXPECT_TRUE(r2 == s.lowestCommonAncestor2(r1, r2, r9));
  EXPECT_SUMMARY;
}

int main()
{
  testLowestCommonAncestor();
  return 0;
}
