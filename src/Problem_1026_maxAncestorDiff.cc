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
  // mi 为父节点的最小值
  // ma 为父节点的最大值
  int f(TreeNode* cur, int mi, int ma)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    int diff = std::max(std::abs(cur->val - mi), std::abs(cur->val - ma));
    mi = std::min(mi, cur->val);
    ma = std::max(ma, cur->val);
    diff = std::max(diff, f(cur->left, mi, ma));
    diff = std::max(diff, f(cur->right, mi, ma));
    return diff;
  }

  int maxAncestorDiff(TreeNode* root) { return f(root, root->val, root->val); }
};

void test()
{
  Solution s;
  TreeNode* x9 = new TreeNode(13, nullptr, nullptr);
  TreeNode* x8 = new TreeNode(7, nullptr, nullptr);
  TreeNode* x7 = new TreeNode(4, nullptr, nullptr);
  TreeNode* x6 = new TreeNode(14, x9, nullptr);
  TreeNode* x5 = new TreeNode(6, x7, x8);
  TreeNode* x4 = new TreeNode(1, nullptr, nullptr);
  TreeNode* x3 = new TreeNode(10, nullptr, x6);
  TreeNode* x2 = new TreeNode(3, x4, x5);
  TreeNode* x1 = new TreeNode(8, x2, x3);

  TreeNode* y4 = new TreeNode(3, nullptr, nullptr);
  TreeNode* y3 = new TreeNode(0, y4, nullptr);
  TreeNode* y2 = new TreeNode(2, nullptr, y3);
  TreeNode* y1 = new TreeNode(1, nullptr, y2);
  EXPECT_EQ_INT(7, s.maxAncestorDiff(x1));
  EXPECT_EQ_INT(3, s.maxAncestorDiff(y1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
