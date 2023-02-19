#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

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

class Solution
{
 public:
  TreeNode *process(vector<int> &pre, int L1, int R1, vector<int> &in, int L2, int R2, unordered_map<int, int> &map)
  {
    if (L1 > R1)
    {
      return nullptr;
    }
    TreeNode *head = new TreeNode(pre[L1]);
    if (L1 == R1)
    {
      return head;
    }
    int findIndex = map[pre[L1]];
    // findIndex - L2 含义是：
    // 在中序序列区间[L2, findIndex)剩余元素的个数
    // 即pre[L1]的左子树节点个数
    head->left = process(pre, L1 + 1, L1 + findIndex - L2, in, L2, findIndex - 1, map);
    head->right = process(pre, L1 + findIndex - L2 + 1, R1, in, findIndex + 1, R2, map);
    return head;
  }

  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
  {
    unordered_map<int, int> map;
    for (int i = 0; i < inorder.size(); i++)
    {
      // 根据题意，节点的值都是唯一的
      // 记录每个值在中序遍历的下标
      map.emplace(inorder[i], i);
    }
    return process(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, map);
  }
};

bool isSameTree(TreeNode *head1, TreeNode *head2)
{
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  if (head1 != nullptr && head2 != nullptr)
  {
    return head1->val == head2->val && isSameTree(head1->left, head2->left) && isSameTree(head1->right, head2->right);
  }
  return false;
}

void testZigzagLevelOrder()
{
  Solution s;
  TreeNode *x5 = new TreeNode(7, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(15, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(20, x4, x5);
  TreeNode *x2 = new TreeNode(9, nullptr, nullptr);
  TreeNode *x1 = new TreeNode(3, x2, x3);
  vector<int> p1 = {3, 9, 20, 15, 7};
  vector<int> i1 = {9, 3, 15, 20, 7};

  TreeNode *y = new TreeNode(-1);
  vector<int> p2 = {-1};
  vector<int> i2 = {-1};

  EXPECT_TRUE(isSameTree(x1, s.buildTree(p1, i1)));
  EXPECT_TRUE(isSameTree(y, s.buildTree(p2, i2)));
  EXPECT_SUMMARY;
}

int main()
{
  testZigzagLevelOrder();
  return 0;
}
