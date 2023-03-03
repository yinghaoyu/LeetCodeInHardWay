#include <iostream>
#include <vector>

#include "UnitTest.h"

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
  // Morris遍历
  // 整个遍历的过程跟中序遍历顺序一致
  int kthSmallest(TreeNode *root, int k)
  {
    if (root == nullptr)
    {
      return -1;
    }
    TreeNode *cur = root;
    TreeNode *mostRight = nullptr;
    int index = 1;
    while (cur != nullptr)
    {
      // 先从遍历cur的左孩子
      mostRight = cur->left;
      if (mostRight != nullptr)
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          // 找到cur的左孩子的最右节点
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          // 第一次遍历到，就把这个节点的右孩子指向cur
          // 这个思维符合中序遍历，mostRight是cur前面的一个节点
          mostRight->right = cur;
          // 一直往左，先把每个cur节点的mostRight指向cur
          cur = cur->left;
          continue;
        }
        else
        {
          // 第二次回溯遍历到，恢复这个节点的指针
          mostRight->right = nullptr;
        }
      }
      // 到这里左孩子已经遍历完毕
      if (index++ == k)
      {
        return cur->val;
      }
      // 开始遍历cur的右孩子
      cur = cur->right;
    }
    return -1;
  }
};

void testKthSmallest()
{
  Solution s;
  TreeNode *t4 = new TreeNode(2, nullptr, nullptr);
  TreeNode *t3 = new TreeNode(4, nullptr, nullptr);
  TreeNode *t2 = new TreeNode(1, nullptr, t4);
  TreeNode *t1 = new TreeNode(3, t2, t3);

  TreeNode *r6 = new TreeNode(1, nullptr, nullptr);
  TreeNode *r5 = new TreeNode(4, nullptr, nullptr);
  TreeNode *r4 = new TreeNode(2, r6, nullptr);
  TreeNode *r3 = new TreeNode(6, nullptr, nullptr);
  TreeNode *r2 = new TreeNode(3, r4, r5);
  TreeNode *r1 = new TreeNode(5, r2, r3);
  EXPECT_EQ_INT(1, s.kthSmallest(t1, 1));
  EXPECT_EQ_INT(3, s.kthSmallest(r1, 3));
  EXPECT_SUMMARY;
}

int main()
{
  testKthSmallest();
  return 0;
}
