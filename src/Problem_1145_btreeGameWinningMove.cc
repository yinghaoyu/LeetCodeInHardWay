#include <algorithm>
#include <functional>

#include "UnitTest.h"

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 参考链接：https://leetcode.cn/problems/binary-tree-coloring-game/solution/mei-you-si-lu-yi-zhang-tu-miao-dong-pyth-btav/
class Solution
{
 public:
  bool btreeGameWinningMove(TreeNode *root, int n, int x)
  {
    // x节点为1号玩家起始点
    // x节点左子树节点数量 lsize
    // x节点右子树节点数量 rsize
    // x父节点子树的节点数量fsize = n - 1 - lsize - rsize
    // 2号玩家选3者的最大值
    // 那么2号玩家能感染的节点最大值为n0 = max(lsize, rsize, fsize)
    // 1号玩家感染的节点为 n - n0
    // 2号玩家赢，必须满足 n0 > n - n0
    int lsize = 0;
    int rsize = 0;
    std::function<int(TreeNode *)> dfs = [&](TreeNode *node) {
      if (node == nullptr)
      {
        return 0;
      }
      int l = dfs(node->left);
      int r = dfs(node->right);
      if (node->val == x)
      {
        lsize = l;
        rsize = r;
      }
      return l + r + 1;
    };
    dfs(root);
    return std::max({lsize, rsize, n - 1 - lsize - rsize}) * 2 > n;
  }
};

void testBtreeGameWinningMove()
{
  Solution s;
  TreeNode *r11 = new TreeNode(11, nullptr, nullptr);
  TreeNode *r10 = new TreeNode(10, nullptr, nullptr);
  TreeNode *r9 = new TreeNode(9, nullptr, nullptr);
  TreeNode *r8 = new TreeNode(8, nullptr, nullptr);
  TreeNode *r7 = new TreeNode(7, nullptr, nullptr);
  TreeNode *r6 = new TreeNode(6, nullptr, nullptr);
  TreeNode *r5 = new TreeNode(5, r10, r11);
  TreeNode *r4 = new TreeNode(4, r8, r9);
  TreeNode *r3 = new TreeNode(3, r6, r7);
  TreeNode *r2 = new TreeNode(2, r4, r5);
  TreeNode *r1 = new TreeNode(1, r2, r3);

  TreeNode *x3 = new TreeNode(3, nullptr, nullptr);
  TreeNode *x2 = new TreeNode(2, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(1, x2, x3);
  EXPECT_TRUE(s.btreeGameWinningMove(r1, 11, 3));
  EXPECT_FALSE(s.btreeGameWinningMove(x1, 3, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testBtreeGameWinningMove();
  return 0;
}
