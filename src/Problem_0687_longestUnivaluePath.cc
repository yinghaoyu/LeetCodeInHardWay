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
  int process(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    int left = process(cur->left);
    int right = process(cur->right);
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

  int longestUnivaluePath(TreeNode *root)
  {
    process(root);
    return ans;
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
  s.longestUnivaluePath(x1);
  EXPECT_EQ_INT(2, s.longestUnivaluePath(x1));
  EXPECT_EQ_INT(2, s.longestUnivaluePath(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestUnivaluePath();
  return 0;
}
