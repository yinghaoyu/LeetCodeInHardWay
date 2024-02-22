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
    f(cur->left, ans);
    f(cur->right, ans);
    ans.push_back(cur->val);
  }

  // 递归
  vector<int> postorderTraversal1(TreeNode* root)
  {
    vector<int> ans;
    f(root, ans);
    return ans;
  }

  // 迭代
  vector<int> postorderTraversal2(TreeNode* root)
  {
    if (root == nullptr)
    {
      return {};
    }
    vector<int> ans;
    stack<TreeNode*> stA;
    stack<TreeNode*> stB;

    stA.push(root);
    while (!stA.empty())
    {
      TreeNode* cur = stA.top();
      stA.pop();
      // 进栈顺序为 根 右 左
      stB.push(cur);
      if (cur->left != nullptr)
      {
        stA.push(cur->left);
      }
      if (cur->right != nullptr)
      {
        stA.push(cur->right);
      }
    }
    while (!stB.empty())
    {
      // 出栈顺序为 左 右 根
      TreeNode* cur = stB.top();
      stB.pop();
      ans.push_back(cur->val);
    }
    return ans;
  }

  TreeNode* reverseEdge(TreeNode* from)
  {
    TreeNode* pre = nullptr;
    TreeNode* next = nullptr;
    while (from != nullptr)
    {
      next = from->right;
      from->right = pre;
      pre = from;
      from = next;
    }
    return pre;
  }

  void printEdge(TreeNode* head, vector<int>& ans)
  {
    TreeNode* tail = reverseEdge(head);
    TreeNode* cur = tail;
    while (cur != nullptr)
    {
      ans.push_back(cur->val);
      cur = cur->right;
    }
    reverseEdge(tail);
  }

  // TODO: figure it out.
  // Morris遍历 实现后序遍历
  vector<int> postorderTraversal3(TreeNode* head)
  {
    if (head == nullptr)
    {
      return {};
    }
    vector<int> ans;
    TreeNode* cur = head;
    TreeNode* mostRight = nullptr;
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
          printEdge(cur->left, ans);
        }
      }
      cur = cur->right;
    }
    printEdge(head, ans);
    return ans;
  }
};
