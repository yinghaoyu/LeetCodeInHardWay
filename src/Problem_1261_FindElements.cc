#include <functional>

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

// @sa
// https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/solutions/2681672/liang-chong-fang-fa-ha-xi-biao-wei-yun-s-6m7w/
class FindElements
{
 private:
  TreeNode* root;

 public:
  void dfs(TreeNode* cur)
  {
    if (cur == nullptr)
    {
      return;
    }
    if (cur->left)
    {
      cur->left->val = 2 * cur->val + 1;
    }
    if (cur->right)
    {
      cur->right->val = 2 * cur->val + 2;
    }
    dfs(cur->left);
    dfs(cur->right);
  }

  FindElements(TreeNode* root)
  {
    this->root = root;
    root->val = 0;
    dfs(root);
  }

  bool find(int target)
  {
    // target 就相当于这里面的节点值，这里相当于判断target对应这个节点是否存在
    // 所以target加一就相当于节点加一
    target++;
    TreeNode* cur = root;
    // 32位 32-k(前导0个数) 得到target的二进制位数x
    // x-1得最高位下标j
    // 最高位下标-1得次高位下标32-k-1-1 => 30-k
    int k = 32 - __builtin_clz(target) - 1 - 1;
    while (cur != nullptr && k >= 0)
    {
      if ((target & (1 << k)) == 0)
      {
        // 偶数往左边走
        cur = cur->left;
      }
      else
      {
        // 奇数往右边走
        cur = cur->right;
      }
      k--;
    }
    return cur != nullptr;
  }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
