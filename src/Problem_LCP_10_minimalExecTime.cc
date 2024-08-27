#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// @sa
// https://leetcode.cn/problems/er-cha-shu-ren-wu-diao-du/solutions/2105203/jian-ji-jie-lun-zheng-ming-tu-jie-by-new-3jz0/
class Solution
{
 public:
  std::pair<double, double> f(TreeNode* cur)
  {
    if (cur == nullptr)
    {
      return {0, 0};
    }
    auto [s1, t1] = f(cur->left);
    auto [s2, t2] = f(cur->right);
    return {s1 + s2 + cur->val, std::max(std::max(t1, t2), (s1 + s2) / 2) + cur->val};
  }

  double minimalExecTime(TreeNode* root) { return f(root).second; }
};
