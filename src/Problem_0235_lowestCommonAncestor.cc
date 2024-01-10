#include <algorithm>

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
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
  {
    // root从上到下
    // 如果先遇到了p，说明p是答案
    // 如果先遇到了q，说明q是答案
    // 如果root在p~q的值之间，不用管p和q谁大谁小，只要root在中间，那么此时的root就是答案
    // 如果root在p~q的值的左侧，那么root往右移动
    // 如果root在p~q的值的右侧，那么root往左移动
    while (root->val != p->val && root->val != q->val)
    {
      if (std::min(p->val, q->val) < root->val && root->val < std::max(p->val, q->val))
      {
        break;
      }
      root = root->val < std::min(p->val, q->val) ? root->right : root->left;
    }
    return root;
  }
};
