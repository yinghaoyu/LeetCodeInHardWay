#include <iostream>
#include <queue>
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

class CBTInserter
{
 private:
  queue<TreeNode *> candidates;
  TreeNode *root;

 public:
  CBTInserter(TreeNode *root)
  {
    this->root = root;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
      TreeNode *cur = q.front();
      q.pop();
      if (cur->left)
      {
        q.push(cur->left);
      }
      if (cur->right)
      {
        q.push(cur->right);
      }
      if (cur->left == nullptr || cur->right == nullptr)
      {
        candidates.push(cur);
      }
    }
  }

  int insert(int val)
  {
    TreeNode *node = new TreeNode(val);
    TreeNode *cur = candidates.front();
    if (cur->left == nullptr)
    {
      cur->left = node;
    }
    else if (cur->right == nullptr)
    {
      cur->right = node;
      candidates.pop();
    }
    candidates.push(node);
    return cur->val;
  }

  TreeNode *get_root() { return root; }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
