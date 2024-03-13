#include <stdint.h>
#include <algorithm>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
  class Info
  {
   public:
    long min;
    long max;
    bool isBST;
    Info(long min, long max, bool bst)
    {
      this->min = min;
      this->max = max;
      this->isBST = bst;
    }
  };

 public:
  Info f(TreeNode* cur)
  {
    if (cur == nullptr)
    {
      return Info(INT64_MAX, INT64_MIN, true);
    }

    Info left = f(cur->left);
    Info right = f(cur->right);
    long min = std::min({left.min, right.min, (long) cur->val});
    long max = std::max({left.max, right.max, (long) cur->val});
    bool isBST = true;
    if (!left.isBST || !right.isBST || cur->val <= left.max || right.min <= cur->val)
    {
      isBST = false;
    }
    return Info(min, max, isBST);
  }

  bool isValidBST(TreeNode* root) { return f(root).isBST; }
};
