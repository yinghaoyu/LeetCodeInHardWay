#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
  {
    this->val = x;
    this->left = left;
    this->right = right;
  }
};

class Solution
{
 public:
  TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
  {
    TreeNode *mostRight = nullptr;
    TreeNode *cur = root;
    TreeNode *ans = nullptr;
    TreeNode *pre = nullptr;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight != nullptr)
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          mostRight->right = cur;
          cur = cur->left;
          continue;
        }
        else
        {
          mostRight->right = nullptr;
        }
      }
      if (ans == nullptr && pre == p)
      {
        ans = cur;
      }
      else
      {
        pre = cur;
      }
      cur = cur->right;
    }
    return ans;
  }
};

void testInorderSuccessor()
{
  Solution s;
  TreeNode *x3 = new TreeNode(3, nullptr, nullptr);
  TreeNode *x2 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(2, x2, x3);

  TreeNode *y6 = new TreeNode(1, nullptr, nullptr);
  TreeNode *y5 = new TreeNode(4, nullptr, nullptr);
  TreeNode *y4 = new TreeNode(2, y6, nullptr);
  TreeNode *y3 = new TreeNode(6, nullptr, nullptr);
  TreeNode *y2 = new TreeNode(3, y4, y5);
  TreeNode *y1 = new TreeNode(5, y2, y3);
  EXPECT_TRUE(x1 == s.inorderSuccessor(x1, x2));
  EXPECT_TRUE(nullptr == s.inorderSuccessor(y1, y3));
  EXPECT_SUMMARY;
}

int main()
{
  testInorderSuccessor();
  return 0;
}
