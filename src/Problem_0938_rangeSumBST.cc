#include <queue>
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
  int f(TreeNode* cur, int low, int high)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    if (cur->val < low)
    {
      return f(cur->right, low, high);
    }
    if (cur->val > high)
    {
      return f(cur->left, low, high);
    }
    return cur->val + f(cur->left, low, high) + f(cur->right, low, high);
  }
  // dfs
  int rangeSumBST1(TreeNode* root, int low, int high) { return f(root, low, high); }

  // bfs
  int rangeSumBST2(TreeNode* root, int low, int high)
  {
    int sum = 0;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
      TreeNode* cur = q.front();
      q.pop();
      if (cur == nullptr)
      {
        continue;
      }
      if (cur->val < low)
      {
        q.push(cur->right);
      }
      else if (cur->val > high)
      {
        q.push(cur->left);
      }
      else
      {
        sum += cur->val;
        q.push(cur->left);
        q.push(cur->right);
      }
    }
    return sum;
  }
};
