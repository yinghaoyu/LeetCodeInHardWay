#include <vector>
#include <iostream>

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
 private:
  class Info
  {
   public:
    int height;
    bool isBalanced;
    Info()
    {
      height = 0;
      isBalanced = false;
    }
    Info(int h, bool t)
    {
      height = h;
      isBalanced = t;
    }
  };

 public:
  Info dfs(TreeNode *cur)
  {
    if (cur == nullptr)
    {
      return Info(0, true);
    }
    auto [lh, lb] = dfs(cur->left);
    auto [rh, rb] = dfs(cur->right);
    return Info(std::max(lh, rh) + 1, std::abs(lh - rh) <= 1 && lb && rb);
  }

  bool isBalanced(TreeNode *root) { return dfs(root).isBalanced; }
};
