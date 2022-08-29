#include <iostream>
#include <unordered_map>
#include <vector>

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
  void process(TreeNode *cur, int depth, int no, int &ans, std::unordered_map<int, int> &numbers)
  {
    if (cur == nullptr)
    {
      return;
    }
    if (numbers.find(depth) == numbers.end())
    {
      numbers[depth] = no;
    }
    ans = std::max(ans, no - numbers[depth] + 1);
    // 每次都重新编号，防止树退化成链表导致no << 1 溢出
    no = no - numbers[depth] + 1;
    process(cur->left, depth + 1, no << 1, ans, numbers);
    process(cur->right, depth + 1, (no << 1) | 1, ans, numbers);
  }

  int widthOfBinaryTree(TreeNode *root)
  {
    int ans = 0;
    std::unordered_map<int, int> numbers;
    // 编号从1开始
    process(root, 0, 1, ans, numbers);
    return ans;
  }
};

void testWidthOfBinaryTree()
{
  Solution s;
  TreeNode *x6 = new TreeNode(9, nullptr, nullptr);
  TreeNode *x5 = new TreeNode(3, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(5, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(2, nullptr, x6);
  TreeNode *x2 = new TreeNode(3, x4, x5);
  TreeNode *x1 = new TreeNode(1, x2, x3);

  TreeNode *y7 = new TreeNode(7, nullptr, nullptr);
  TreeNode *y6 = new TreeNode(6, nullptr, nullptr);
  TreeNode *y5 = new TreeNode(9, y7, nullptr);
  TreeNode *y4 = new TreeNode(5, y6, nullptr);
  TreeNode *y3 = new TreeNode(2, nullptr, y5);
  TreeNode *y2 = new TreeNode(3, y4, nullptr);
  TreeNode *y1 = new TreeNode(1, y2, y3);

  TreeNode *z4 = new TreeNode(5, nullptr, nullptr);
  TreeNode *z3 = new TreeNode(2, nullptr, nullptr);
  TreeNode *z2 = new TreeNode(3, z4, nullptr);
  TreeNode *z1 = new TreeNode(1, z2, z3);

  EXPECT_EQ_INT(4, s.widthOfBinaryTree(x1));
  EXPECT_EQ_INT(7, s.widthOfBinaryTree(y1));
  EXPECT_EQ_INT(2, s.widthOfBinaryTree(z1));
  EXPECT_SUMMARY;
}

int main()
{
  testWidthOfBinaryTree();
  return 0;
}
