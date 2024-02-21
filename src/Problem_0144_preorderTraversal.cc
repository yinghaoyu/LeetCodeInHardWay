#include <algorithm>
#include <stack>
#include <vector>

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
  void f(TreeNode* cur, vector<int>& ans)
  {
    if (cur == nullptr)
    {
      return;
    }
    ans.push_back(cur->val);
    f(cur->left, ans);
    f(cur->right, ans);
  }

  // 递归
  vector<int> preorderTraversal1(TreeNode* root)
  {
    vector<int> ans;
    f(root, ans);
    return ans;
  }

  // 迭代
  vector<int> preorderTraversal2(TreeNode* root)
  {
    if (root == nullptr)
    {
      return {};
    }
    vector<int> ans;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty())
    {
      TreeNode* cur = st.top();
      st.pop();
      // 根 左 右
      ans.push_back(cur->val);
      if (cur->right != nullptr)
      {
        st.push(cur->right);
      }
      if (cur->left != nullptr)
      {
        st.push(cur->left);
      }
    }
    return ans;
  }

  // Morris遍历
  vector<int> preorderTraversal3(TreeNode* root)
  {
    if (root == nullptr)
    {
      return {};
    }
    vector<int> ans;
    TreeNode* cur = root;
    TreeNode* mostRight = nullptr;
    while (cur != nullptr)
    {
      // 先指向左孩子
      mostRight = cur->left;
      if (mostRight != nullptr)  // 存在左孩子
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          // 第一次遍历指向 cur
          mostRight->right = cur;
          ans.push_back(cur->val);
          // 继续遍历左孩子
          cur = cur->left;
          continue;
        }
        else
        {
          // 第二次遍历恢复为叶子节点
          mostRight->right = nullptr;
        }
      }
      else
      {
        // 没有左孩子的节点只会遍历一次
        ans.push_back(cur->val);
      }
      // 左孩子，根都遍历完了，处理右孩子
      cur = cur->right;
    }
    return ans;
  }
};
