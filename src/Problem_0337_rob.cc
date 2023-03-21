#include <iostream>

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
 private:
  class Info
  {
   public:
    int no;   // 整颗子树，在不抢头结点的情况下，获得最好的收益
    int yes;  // 整颗子树，在抢头结点的情况下，获得最好的收益
    Info(int n, int y)
    {
      no = n;
      yes = y;
    }
  };

 public:
  Info process(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return Info(0, 0);
    }
    Info left = process(cur->left);
    Info right = process(cur->right);
    int no = std::max(left.yes, left.no) + std::max(right.yes, right.no);
    int yes = cur->val + left.no + right.no;
    return Info(no, yes);
  }

  int rob(TreeNode *root)
  {
    Info info = process(root);
    return std::max(info.yes, info.no);
  }
};

void testRob()
{
  Solution s;
  TreeNode *x5 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(3, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(3, nullptr, x5);
  TreeNode *x2 = new TreeNode(2, nullptr, x4);
  TreeNode *x1 = new TreeNode(3, x2, x3);

  TreeNode *y6 = new TreeNode(1, nullptr, nullptr);
  TreeNode *y5 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y4 = new TreeNode(1, nullptr, nullptr);
  TreeNode *y3 = new TreeNode(5, nullptr, y6);
  TreeNode *y2 = new TreeNode(4, y4, y5);
  TreeNode *y1 = new TreeNode(3, y2, y3);
  EXPECT_EQ_INT(7, s.rob(x1));
  EXPECT_EQ_INT(9, s.rob(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testRob();
  return 0;
}
