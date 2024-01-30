#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
 private:
  class Info
  {
   public:
    int max;
    int min;
    bool isBst;
    int maxBstSize;

    Info(int a, int b, bool c, int d)
    {
      max = a;
      min = b;
      isBst = c;
      maxBstSize = d;
    }
  };

  Info f(TreeNode* x)
  {
    if (x == nullptr)
    {
      return Info(INT32_MIN, INT32_MAX, true, 0);
    }
    Info left = f(x->left);
    Info right = f(x->right);
    int max = std::max({x->val, left.max, right.max});
    int min = std::min({x->val, left.min, right.min});
    bool isBst = left.isBst && right.isBst && left.max < x->val && x->val < right.min;
    int maxBstSize = 0;
    if (isBst)
    {
      maxBstSize = left.maxBstSize + right.maxBstSize + 1;
    }
    else
    {
      maxBstSize = std::max(left.maxBstSize, right.maxBstSize);
    }
    return Info(max, min, isBst, maxBstSize);
  }

 public:
  int largestBSTSubtree(TreeNode* root) { return f(root).maxBstSize; }
};
