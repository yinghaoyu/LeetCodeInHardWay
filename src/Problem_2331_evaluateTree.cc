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
  bool dfs(TreeNode *node)
  {
    switch (node->val)
    {
    case 0:
      return false;
    case 1:
      return true;
    case 2:
      return dfs(node->left) | dfs(node->right);
    case 3:
      return dfs(node->left) & dfs(node->right);
    default:
      return true;
    }
  }

  bool evaluateTree(TreeNode *root) { return dfs(root); }
};

void testEvaluateTree()
{
  Solution s;
  TreeNode *x5 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(0, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(3, x4, x5);
  TreeNode *x2 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(2, x2, x3);

  TreeNode *y = new TreeNode(0);
  EXPECT_TRUE(s.evaluateTree(x1));
  EXPECT_FALSE(s.evaluateTree(y));
  EXPECT_SUMMARY;
}

int main()
{
  testEvaluateTree();
  return 0;
}
