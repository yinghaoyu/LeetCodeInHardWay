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
  TreeNode *bstToGst(TreeNode *root)
  {
    int sum = 0;
    std::function<void(TreeNode *)> dfs = [&](TreeNode *cur)
    {
      if (cur == nullptr)
      {
        return;
      }
      dfs(cur->right);
      sum += cur->val;
      cur->val = sum;
      dfs(cur->left);
    };
    dfs(root);
    return root;
  }
  // 反向 Morris 遍历
  // see at Problem_STOII_0054_convertBST.cc
};
