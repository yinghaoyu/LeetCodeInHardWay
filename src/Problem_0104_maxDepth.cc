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
  int process(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    return std::max(process(cur->left), process(cur->right)) + 1;
  }

  int maxDepth(TreeNode *root) { return process(root); }
};

void testZigzagLevelOrder()
{
  Solution s;
  TreeNode *x5 = new TreeNode(7, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(15, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(20, x4, x5);
  TreeNode *x2 = new TreeNode(9, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(3, x2, x3);

  TreeNode *y2 = new TreeNode(2, nullptr, nullptr);
  TreeNode *y1 = new TreeNode(1, nullptr, y2);

  EXPECT_EQ_INT(3, s.process(x1));
  EXPECT_EQ_INT(2, s.process(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testZigzagLevelOrder();
  return 0;
}
