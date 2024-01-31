#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
 private:
  class Info
  {
   public:
    int maxDistance;
    int height;

    Info(int m, int h)
    {
      maxDistance = m;
      height = h;
    }
  };

 public:
  int diameterOfBinaryTree(TreeNode* root) { return process(root).maxDistance; }

  Info process(TreeNode* x)
  {
    if (x == nullptr)
    {
      return Info(0, 0);
    }
    Info left = process(x->left);
    Info right = process(x->right);
    int maxDistance =
        std::max(std::max(left.maxDistance, right.maxDistance), left.height + right.height);
    int height = std::max(left.height, right.height) + 1;
    return Info(maxDistance, height);
  }
};

void testDiameterOfBinaryTree()
{
  Solution s;
  TreeNode* x5 = new TreeNode(5, nullptr, nullptr);
  TreeNode* x4 = new TreeNode(4, nullptr, nullptr);
  TreeNode* x3 = new TreeNode(3, nullptr, nullptr);
  TreeNode* x2 = new TreeNode(2, x4, x5);
  TreeNode* x1 = new TreeNode(1, x2, x3);
  EXPECT_EQ_INT(3, s.diameterOfBinaryTree(x1));
  EXPECT_SUMMARY;
}

int main()
{
  testDiameterOfBinaryTree();
  return 0;
}
