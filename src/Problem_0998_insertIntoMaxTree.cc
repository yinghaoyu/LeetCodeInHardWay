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
  TreeNode *process(TreeNode *cur, int val)
  {
    if (cur == nullptr)
    {
      return new TreeNode(val, nullptr, nullptr);
    }
    if (cur->val < val)
    {
      TreeNode *node = new TreeNode(val, cur, nullptr);
      return node;
    }
    cur->right = process(cur->right, val);
    return cur;
  }
  TreeNode *insertIntoMaxTree(TreeNode *root, int val) { return process(root, val); }
};

bool isSameValueStructure(TreeNode *head1, TreeNode *head2)
{
  if (head1 == nullptr && head2 != nullptr)
  {
    return false;
  }
  if (head1 != nullptr && head2 == nullptr)
  {
    return false;
  }
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  if (head1->val != head2->val)
  {
    return false;
  }
  return isSameValueStructure(head1->left, head2->left) && isSameValueStructure(head1->right, head2->right);
}

void testInsertIntoMaxTree()
{
  Solution s;
  TreeNode *x1 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x2 = new TreeNode(2, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(3, x2, nullptr);
  TreeNode *x4 = new TreeNode(4, x1, x3);
  TreeNode *x5 = new TreeNode(5, x4, nullptr);

  TreeNode *y1 = new TreeNode(1, nullptr, nullptr);
  TreeNode *y2 = new TreeNode(2, nullptr, y1);
  TreeNode *y3 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y4 = new TreeNode(4, nullptr, nullptr);
  TreeNode *y5 = new TreeNode(5, y2, y4);

  TreeNode *y44 = new TreeNode(4, nullptr, y3);
  TreeNode *y55 = new TreeNode(5, y2, y44);

  TreeNode *z1 = new TreeNode(1, nullptr, nullptr);
  TreeNode *z2 = new TreeNode(2, nullptr, z1);
  TreeNode *z3 = new TreeNode(3, nullptr, nullptr);
  TreeNode *z4 = new TreeNode(4, z3, nullptr);
  TreeNode *z5 = new TreeNode(5, z2, z3);

  TreeNode *z55 = new TreeNode(5, z2, z4);

  EXPECT_TRUE(isSameValueStructure(x5, s.insertIntoMaxTree(x4, 5)));
  EXPECT_TRUE(isSameValueStructure(y55, s.insertIntoMaxTree(y5, 3)));
  EXPECT_TRUE(isSameValueStructure(z55, s.insertIntoMaxTree(z5, 4)));

  EXPECT_SUMMARY;
}

int main()
{
  testInsertIntoMaxTree();
};
