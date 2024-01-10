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
  vector<vector<int>> pathSum(TreeNode* root, int targetSum)
  {
    vector<vector<int>> ans;
    if (root != nullptr)
    {
      vector<int> path;
      f(root, targetSum, 0, path, ans);
    }
    return ans;
  }

  void f(TreeNode* cur, int aim, int sum, vector<int>& path, vector<vector<int>>& ans)
  {
    if (cur->left == nullptr && cur->right == nullptr)
    {
      // 是叶子节点
      if (cur->val + sum == aim)
      {
        path.push_back(cur->val);
        ans.push_back(path);
        path.pop_back();  // backtrace
      }
    }
    else
    {
      // 不是叶子节点
      path.push_back(cur->val);
      if (cur->left != nullptr)
      {
        f(cur->left, aim, sum + cur->val, path, ans);
      }
      if (cur->right != nullptr)
      {
        f(cur->right, aim, sum + cur->val, path, ans);
      }
      path.pop_back();
    }
  }
};
