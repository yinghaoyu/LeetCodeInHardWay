#include <functional>
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
  TreeNode *increasingBST(TreeNode *root)
  {
    TreeNode *dummy = new TreeNode(-1);
    TreeNode *x = dummy;
    std::function<void(TreeNode *)> dfs = [&](TreeNode *cur)
    {
      if (cur == nullptr)
      {
        return;
      }
      dfs(cur->left);
      // 中序遍历的时候让 cur 的左指针失效，此时左孩子已全部遍历完毕
      x->right = cur;
      cur->left = nullptr;
      x = cur;
      dfs(cur->right);
    };
    dfs(root);
    return dummy->right;
  }
};
