#include <iostream>
#include <vector>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
 public:
  int dfs(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    return std::max(dfs(cur->left), dfs(cur->right)) + 1;
  }

  int maxDepth(TreeNode *root) { return dfs(root); }
};
