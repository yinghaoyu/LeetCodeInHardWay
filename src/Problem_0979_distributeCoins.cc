#include <functional>
#include <iostream>
#include <vector>

#include "UnitTest.h"

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
  // https://leetcode.cn/problems/distribute-coins-in-binary-tree/solution/tu-jie-mei-you-si-lu-jin-lai-miao-dong-p-vrni/
  int distributeCoins(TreeNode* root)
  {
    int ans = 0;
    std::function<int(TreeNode*)> dfs = [&](TreeNode* cur)
    {
      if (cur == nullptr)
      {
        return 0;
      }
      int x = dfs(cur->left) + dfs(cur->right) + cur->val - 1;
      ans += std::abs(x);
      return x;
    };
    dfs(root);
    return ans;
  }
};
