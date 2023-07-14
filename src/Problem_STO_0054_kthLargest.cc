#include <functional>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

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
  int kthLargest(TreeNode *root, int k)
  {
    int ans = 0;
    std::function<void(TreeNode *)> dfs = [&](TreeNode *cur)
    {
      if (cur == nullptr)
      {
        return;
      }
      // 利用中序遍历的倒序
      dfs(cur->right);
      if (--k == 0)
      {
        ans = cur->val;
      }
      dfs(cur->left);
    };
    dfs(root);
    return ans;
  }
};
