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
  void inorder(TreeNode *cur, vector<int> &ans, int i)
  {
    if (cur == nullptr)
    {
      // 记录空节点，防止节点出现相同元素
      //      1
      //     ↙ ↘
      //   2     2
      //  ↙ ↘   ↙
      // 2  N  2
      ans.push_back(101 + i);
      return;
    }
    inorder(cur->left, ans, i + 1);
    ans.push_back(cur->val);
    inorder(cur->right, ans, i + 1);
  }

  bool isSymmetric1(TreeNode *root)
  {
    vector<int> ans;
    inorder(root, ans, 0);
    int n = ans.size();
    for (int i = 0; i <= n / 2; i++)
    {
      if (ans[i] != ans[n - 1 - i])
      {
        return false;
      }
    }
    return true;
  }

  // 一颗是原始树
  // 一颗是翻面树
  bool isMirror(TreeNode *head1, TreeNode *head2)
  {
    if (head1 == nullptr && head2 == nullptr)
    {
      return true;
    }
    if (head1 != nullptr && head2 != nullptr)
    {
      return head1->val == head2->val && isMirror(head1->left, head2->right) && isMirror(head1->right, head2->left);
    }
    // 一个为空，一个不为空 false
    return false;
  }

  bool isSymmetric2(TreeNode *root) { return isMirror(root, root); }
};

void testIsSymmetric()
{
  Solution s;
  TreeNode *x7 = new TreeNode(3, nullptr, nullptr);
  TreeNode *x6 = new TreeNode(4, nullptr, nullptr);
  TreeNode *x5 = new TreeNode(4, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(3, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(2, x6, x7);
  TreeNode *x2 = new TreeNode(2, x4, x5);
  TreeNode *x1 = new TreeNode(3, x2, x3);

  TreeNode *y5 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y4 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y3 = new TreeNode(2, nullptr, y5);
  TreeNode *y2 = new TreeNode(2, nullptr, x4);
  TreeNode *y1 = new TreeNode(1, y2, y3);
  EXPECT_TRUE(s.isSymmetric1(x1));
  EXPECT_FALSE(s.isSymmetric1(y1));
  EXPECT_TRUE(s.isSymmetric2(x1));
  EXPECT_FALSE(s.isSymmetric2(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testIsSymmetric();
  return 0;
}
