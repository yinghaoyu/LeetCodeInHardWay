#include <functional>
#include <iostream>
#include <unordered_set>
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
  bool findTarget(TreeNode *root, int k)
  {
    unordered_set<int> set;
    function<bool(TreeNode *)> dfs = [&](TreeNode *cur)
    {
      if (cur == nullptr)
      {
        return false;
      }
      if (set.count(k - cur->val))
      {
        return true;
      }
      set.emplace(cur->val);
      return dfs(cur->left) || dfs(cur->right);
    };
    return dfs(root);
  }
};
