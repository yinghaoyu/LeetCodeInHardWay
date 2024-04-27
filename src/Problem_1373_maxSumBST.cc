#include <algorithm>

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
 private:
  class Info
  {
   public:
    int max;
    int min;
    int sum;
    bool isBst;
    int maxBstSum;
    Info(int a, int b, int c, bool d, int e)
    {
      max = a;
      min = b;
      sum = c;
      isBst = d;
      maxBstSum = e;
    }
  };

  Info f(TreeNode* x)
  {
    if (x == nullptr)
    {
      return Info(INT32_MIN, INT32_MAX, 0, true, 0);
    }
    Info left = f(x->left);
    Info right = f(x->right);
    int max = std::max({x->val, left.max, right.max});
    int min = std::min({x->val, left.min, right.min});
    int sum = left.sum + right.sum + x->val;
    bool isBst = left.isBst && right.isBst && left.max < x->val && x->val < right.min;
    int maxBstSum = std::max(left.maxBstSum, right.maxBstSum);
    if (isBst)
    {
      maxBstSum = std::max(maxBstSum, sum);
    }
    return Info(max, min, sum, isBst, maxBstSum);
  }

 public:
  int maxSumBST(TreeNode* root) { return f(root).maxBstSum; }
};
