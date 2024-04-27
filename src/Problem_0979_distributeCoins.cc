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

// 树型dp
class Solution
{
 public:
  class Info
  {
   public:
    // 节点总和
    int cnt;
    // 节点值总和
    int sum;
    // 需要走多少步
    int move;

    Info(int a, int b, int c)
    {
      cnt = a;
      sum = b;
      move = c;
    }
  };

  int distributeCoins(TreeNode* root) { return f(root).move; }

  Info f(TreeNode* cur)
  {
    if (cur == nullptr)
    {
      return Info(0, 0, 0);
    }
    Info left = f(cur->left);
    Info right = f(cur->right);
    int cnts = left.cnt + right.cnt + 1;
    int sums = left.sum + right.sum + cur->val;
    int moves =
        left.move + right.move + std::abs(left.cnt - left.sum) + std::abs(right.cnt - right.sum);
    return Info(cnts, sums, moves);
  }
};
