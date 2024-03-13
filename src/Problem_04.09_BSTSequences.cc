#include <algorithm>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
 public:
  void dfs(vector<TreeNode*>& nodes, vector<vector<int>>& ans, vector<int>& path)
  {
    if (nodes.size() == 0)
    {
      ans.push_back(path);
      return;
    }
    // 相同层的节点都可以不同顺序
    for (int i = 0; i < nodes.size(); i++)
    {
      TreeNode* node = nodes[i];
      path.push_back(node->val);
      nodes.erase(nodes.begin() + i);
      if (node->left != NULL)
      {
        nodes.push_back(node->left);
      }
      if (node->right != NULL)
      {
        nodes.push_back(node->right);
      }
      dfs(nodes, ans, path);
      // 回溯
      nodes.insert(nodes.begin() + i, node);
      nodes.erase(std::remove(nodes.begin(), nodes.end(), node->left), nodes.end());
      nodes.erase(std::remove(nodes.begin(), nodes.end(), node->right), nodes.end());
      path.pop_back();
    }
  }

  vector<vector<int>> BSTSequences(TreeNode* root)
  {
    vector<vector<int>> ans;
    if (root == NULL)
    {
      return ans;
    }
    vector<int> path;
    vector<TreeNode*> nodes;
    nodes.push_back(root);
    dfs(nodes, ans, path);
    return ans;
  }
};
