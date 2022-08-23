#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

using TsArray = vector<vector<string>>;

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
  int getDepth(TreeNode *root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    int p1 = getDepth(root->left);
    int p2 = getDepth(root->right);
    return std::max(p1, p2) + 1;
  }

  void process(TreeNode *cur, TsArray &ans, int row, int col, int deep)
  {
    if (cur == nullptr || row >= deep || col >= std::pow(2, deep) - 1)
    {
      return;
    }
    ans[row][col] = std::to_string(cur->val);
    process(cur->left, ans, row + 1, col - std::pow(2, deep - row - 2), deep);
    process(cur->right, ans, row + 1, col + std::pow(2, deep - row - 2), deep);
  }

  TsArray printTree(TreeNode *root)
  {
    int depth = getDepth(root);
    int n = std::pow(2, depth) - 1;
    TsArray ans(depth, vector<string>(n));
    process(root, ans, 0, (n - 1) >> 1, depth);
    return ans;
  }
};

bool isTsArrayEqual(TsArray r1, TsArray r2)
{
  if (r1.size() != r2.size() || r1[0].size() != r2[0].size())
  {
    return false;
  }
  for (int i = 0; i < r1.size(); i++)
  {
    for (int j = 0; j < r1[0].size(); j++)
    {
      if (r1[i][j] != r2[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

void testPrintTree()
{
  Solution s;
  vector<int> v1 = {1, 2};
  TreeNode *x2 = new TreeNode(2, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(1, x2, nullptr);
  TsArray res1 = {{"", "1", ""}, {"2", "", ""}};

  TreeNode *y4 = new TreeNode(4, nullptr, nullptr);
  TreeNode *y3 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y2 = new TreeNode(2, nullptr, y4);
  TreeNode *y1 = new TreeNode(1, y2, y3);
  TsArray res2 = {{"", "", "", "1", "", "", ""}, {"", "2", "", "", "", "3", ""}, {"", "", "4", "", "", "", ""}};

  EXPECT_TRUE(isTsArrayEqual(s.printTree(x1), res1));
  EXPECT_TRUE(isTsArrayEqual(s.printTree(y1), res2));
  EXPECT_SUMMARY;
};

int main()
{
  testPrintTree();
  return 0;
}
