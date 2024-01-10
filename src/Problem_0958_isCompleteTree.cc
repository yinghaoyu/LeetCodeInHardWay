#include <queue>

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
  bool isCompleteTree(TreeNode* root)
  {
    if (root == nullptr)
    {
      return true;
    }
    queue<TreeNode*> que;
    que.push(root);
    // 是否遇到过左右两个孩子不双全的节点
    bool leaf = false;
    while (!que.empty())
    {
      TreeNode* cur = que.front();
      que.pop();
      if ((cur->left == nullptr && cur->right != nullptr) || (leaf && (cur->left != nullptr || cur->right != nullptr)))
      {
        return false;
      }
      if (cur->left != nullptr)
      {
        que.push(cur->left);
      }
      if (cur->right != nullptr)
      {
        que.push(cur->right);
      }
      if (cur->left == nullptr || cur->right == nullptr)
      {
        leaf = true;
      }
    }
    return true;
  }
};
