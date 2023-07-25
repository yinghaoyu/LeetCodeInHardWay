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

// seem as leetcode 0897
// https://leetcode-cn.com/problems/increasing-order-search-tree/
// see at Problem_0897_increasingBST.cc
class Solution
{
 public:
  TreeNode *increasingBST(TreeNode *root)
  {
    TreeNode *dummy = new TreeNode(-1);
    TreeNode *x = dummy;
    function<void(TreeNode *)> dfs = [&](TreeNode *cur)
    {
      if (cur == nullptr)
      {
        return;
      }
      dfs(cur->left);
      x->right = cur;
      cur->left = nullptr;
      x = cur;
      dfs(cur->right);
    };
    dfs(root);
    return dummy->right;
  }
};
