#include <memory>
#include <stack>
#include <type_traits>
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
  void f(TreeNode* node, vector<int>& ans)
  {
    if (node == nullptr)
    {
      return;
    }
    f(node->left, ans);
    ans.push_back(node->val);
    f(node->right, ans);
  }

  // 递归
  vector<int> inorderTraversal1(TreeNode* root)
  {
    vector<int> ans;
    f(root, ans);
    return ans;
  }

  // 迭代
  vector<int> inorderTraversal2(TreeNode* root)
  {
    if (root == nullptr)
    {
      return {};
    }
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (!st.empty() || cur != nullptr)
    {
      if (cur != nullptr)
      {
        // 先把所有左孩子全部入栈
        st.push(cur);
        cur = cur->left;
      }
      else
      {
        cur = st.top();
        st.pop();
        // 出栈的时候处理根节点
        ans.push_back(cur->val);
        // 再处理右孩子，把所有右孩子入栈
        cur = cur->right;
      }
    }
    return ans;
  }

  // Morris遍历
  // 把空间复杂度优化到O(1)的二叉树遍历算法
  vector<int> inorderTraversal3(TreeNode* root)
  {
    vector<int> ans;
    if (root == nullptr)
    {
      return ans;
    }
    TreeNode* cur = root;
    TreeNode* mostRight = nullptr;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight != nullptr)  // 存在左孩子
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          // 找到左孩子最右的节点
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          // 第一次遍历到该节点
          // 把这个指针指向当前节点
          mostRight->right = cur;
          // 遍历左孩子
          cur = cur->left;
          continue;
        }
        else
        {
          // 第二次遍历恢复为叶子节点
          mostRight->right = nullptr;
        }
      }
      // 根
      ans.push_back(cur->val);
      // 左孩子、根都遍历结束，轮到右孩子了
      cur = cur->right;
    }
    return ans;
  }
};

void testInorderTraversal()
{
  Solution s;
  vector<int> o1 = {1, 3, 2};
  TreeNode* x3 = new TreeNode(3);
  TreeNode* x2 = new TreeNode(2, x3, nullptr);
  TreeNode* x1 = new TreeNode(1, nullptr, x2);
  EXPECT_TRUE(o1 == s.inorderTraversal1(x1));
  EXPECT_TRUE(o1 == s.inorderTraversal2(x1));
  EXPECT_TRUE(o1 == s.inorderTraversal3(x1));
  EXPECT_SUMMARY;
}

int main()
{
  testInorderTraversal();
  return 0;
}
