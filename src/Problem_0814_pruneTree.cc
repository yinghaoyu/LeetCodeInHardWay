#include <iostream>
#include <vector>

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
  TreeNode *dfs(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return nullptr;
    }
    cur->left = dfs(cur->left);
    cur->right = dfs(cur->right);
    if (cur->left == nullptr && cur->right == nullptr && cur->val == 0)
    {
      return nullptr;
    }
    return cur;
  }

  TreeNode *pruneTree(TreeNode *root) { return dfs(root); }
};
