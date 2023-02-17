#include <memory>
#include <type_traits>
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
  void process(TreeNode *node, vector<int> &ans)
  {
    if (node == nullptr)
    {
      return;
    }
    process(node->left, ans);
    ans.push_back(node->val);
    process(node->right, ans);
  }

  vector<int> inorderTraversal1(TreeNode *root)
  {
    vector<int> ans;
    process(root, ans);
    return ans;
  }

  // Morris遍历
  // 把空间复杂度优化到O(1)的二叉树遍历算法
  vector<int> inorderTraversal2(TreeNode *root)
  {
    // TODO: figure it out
    vector<int> ans;
    if (root == nullptr)
    {
      return ans;
    }
    TreeNode *cur = root;
    TreeNode *mostRight = nullptr;
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
      ans.push_back(cur->val);
      cur = cur->right;
    }
    return ans;
  }
};

void testInorderTraversal()
{
  Solution s;
  vector<int> o1 = {1, 3, 2};
  TreeNode *x3 = new TreeNode(3);
  TreeNode *x2 = new TreeNode(2, x3, nullptr);
  TreeNode *x1 = new TreeNode(1, nullptr, x2);
  EXPECT_TRUE(o1 == s.inorderTraversal1(x1));
  EXPECT_TRUE(o1 == s.inorderTraversal2(x1));
  EXPECT_SUMMARY;
}

int main()
{
  testInorderTraversal();
  return 0;
}
