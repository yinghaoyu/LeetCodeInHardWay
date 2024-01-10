#include <iostream>
#include <stack>
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
 public:
  void inorder(TreeNode* cur, vector<int>& ans)
  {
    if (cur == nullptr)
    {
      return;
    }
    inorder(cur->left, ans);
    ans.push_back(cur->val);
    inorder(cur->right, ans);
  }

  // 中序遍历，递归
  bool isValidBST1(TreeNode* root)
  {
    vector<int> ans;
    inorder(root, ans);
    for (int i = 1; i < ans.size(); i++)
    {
      if (ans[i - 1] >= ans[i])
      {
        return false;
      }
    }
    return true;
  }

  // 中序遍历，非递归
  bool isValidBST2(TreeNode* root)
  {
    if (root == nullptr)
    {
      return true;
    }
    TreeNode* pre = nullptr;
    TreeNode* cur = root;
    stack<TreeNode*> stack;
    while (cur != nullptr || !stack.empty())
    {
      if (cur != nullptr)
      {
        stack.push(cur);
        cur = cur->left;
      }
      else
      {
        cur = stack.top();
        stack.pop();
        if (pre != nullptr && pre->val >= cur->val)
        {
          return false;
        }
        pre = cur;
        cur = cur->right;
      }
    }
    return true;
  }

  class Info
  {
   public:
    int max;
    int min;
    bool isBST;
    Info(int ma, int mi, bool b)
    {
      max = ma;
      min = mi;
      isBST = b;
    }
  };

  // 递归
  Info f(TreeNode* cur)
  {
    if (cur == nullptr)
    {
      return Info(INT32_MIN, INT32_MAX, true);
    }
    bool isBST = true;
    Info l = f(cur->left);
    Info r = f(cur->right);
    if (!l.isBST)
    {
      isBST = false;
    }
    if (!r.isBST)
    {
      isBST = false;
    }
    if (l.max >= cur->val || cur->val >= r.min)
    {
      isBST = false;
    }
    int max = cur->val;
    max = std::max(max, l.max);
    max = std::max(max, r.max);

    int min = cur->val;
    min = std::min(min, l.min);
    min = std::min(min, r.min);
    return Info(max, min, isBST);
  }

  bool isValidBST3(TreeNode* root) { return f(root).isBST; }

  // Morris遍历
  bool isValidBST4(TreeNode* root)
  {
    if (root == nullptr)
    {
      return true;
    }
    TreeNode* cur = root;
    TreeNode* mostRight = nullptr;
    int pre = 0;
    bool ans = true;
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
      if (pre != 0 && pre >= cur->val)
      {
        ans = false;
      }
      pre = cur->val;
      cur = cur->right;
    }
    return ans;
  }
};

void testIsValidBST()
{
  Solution s;
  TreeNode* x3 = new TreeNode(3);
  TreeNode* x1 = new TreeNode(1);
  TreeNode* x2 = new TreeNode(2, x1, x3);

  TreeNode* y6 = new TreeNode(6);
  TreeNode* y3 = new TreeNode(3);
  TreeNode* y4 = new TreeNode(4, y3, y6);
  TreeNode* y1 = new TreeNode(1);
  TreeNode* y5 = new TreeNode(5, y1, y4);
  EXPECT_TRUE(s.isValidBST1(x2));
  EXPECT_FALSE(s.isValidBST1(y5));
  EXPECT_TRUE(s.isValidBST3(x2));
  EXPECT_FALSE(s.isValidBST3(y5));
  EXPECT_TRUE(s.isValidBST4(x2));
  EXPECT_FALSE(s.isValidBST4(y5));
  EXPECT_SUMMARY;
}

int main()
{
  testIsValidBST();
  return 0;
}
