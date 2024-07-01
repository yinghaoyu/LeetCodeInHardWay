#include <iostream>
#include <ratio>

#include "UnitTest.h"

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  TreeNode(int x, TreeNode* l, TreeNode* r)
  {
    val = x;
    left = l;
    right = r;
  }
};

class Solution
{
 private:
  class Info
  {
   public:
    TreeNode* ans;
    bool findO1;  // 左边有没有找到 o1 o2
    bool findO2;  // 右边有没有找到 o1 o2

    Info(TreeNode* node, bool f1, bool f2)
    {
      ans = node;
      findO1 = f1;
      findO2 = f2;
    }
  };

 public:
  Info f(TreeNode* x, TreeNode* o1, TreeNode* o2)
  {
    if (x == nullptr)
    {
      return Info(nullptr, false, false);
    }
    Info left = f(x->left, o1, o2);
    Info right = f(x->right, o1, o2);
    bool findO1 = x == o1 || left.findO1 || right.findO1;
    bool findO2 = x == o2 || left.findO2 || right.findO2;
    TreeNode* ans = nullptr;
    if (left.ans != nullptr)
    {
      ans = left.ans;
    }
    if (right.ans != nullptr)
    {
      ans = right.ans;
    }
    if (ans == nullptr)
    {
      // 左右子树都找到对应的节点，返回父节点
      if (findO1 && findO2)
      {
        ans = x;
      }
    }
    return Info(ans, findO1, findO2);
  }

  TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q)
  {
    return f(root, p, q).ans;
  }

  TreeNode* dfs(TreeNode* x, TreeNode* p, TreeNode* q)
  {
    if (x == nullptr || x == p || x == q)
    {
      return x;
    }
    TreeNode* left = dfs(x->left, p, q);
    TreeNode* right = dfs(x->right, p, q);
    if (left == nullptr)
    {
      return right;
    }
    if (right == nullptr)
    {
      return left;
    }
    return x;
  }

  TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)
  {
    return dfs(root, p, q);
  }

  // TODO: figure it out.
  // Morris
  TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q)
  {
    if (preOrder(p->left, p, q) != nullptr || preOrder(p->right, p, q))
    {
      return p;
    }
    if (preOrder(q->left, p, q) != nullptr || preOrder(q->right, p, q))
    {
      return q;
    }
    TreeNode* left = preOrder(root, p, q);
    TreeNode* cur = root;
    TreeNode* mostRight = nullptr;
    TreeNode* lca = nullptr;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight != nullptr)
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          mostRight->right = cur;
          cur = cur->left;
          continue;
        }
        else
        {
          mostRight->right = nullptr;
          if (lca == nullptr)
          {
            // 检查left是否在cur左树的右边界上
            if (rightCheck(cur->left, left))
            {
              if (preOrder(left->right, p, q) != nullptr)
              {
                lca = left;
              }
              left = cur;
              // 为什么此时检查的是left而不是cur
              // 因为cur右树上的某些右指针可能没有恢复回来
              // 需要等右指针恢复回来之后检查才不出错
              // 所以此时检查的是left而不是cur
            }
          }
        }
      }
      cur = cur->right;
    }
    // 如果morris遍历结束了还没有收集到答案
    // 此时最后一个left还没有验证，它一定是答案
    return lca != nullptr ? lca : left;
  }

  bool rightCheck(TreeNode* head, TreeNode* target)
  {
    while (head != nullptr)
    {
      if (head == target)
      {
        return true;
      }
      head = head->right;
    }
    return false;
  }

  // 以head为头的树进行先序遍历，o1和o2谁先被找到就返回谁
  TreeNode* preOrder(TreeNode* head, TreeNode* o1, TreeNode* o2)
  {
    TreeNode* cur = head;
    TreeNode* mostRight = nullptr;
    TreeNode* ans = nullptr;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight != nullptr)
      {
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          if (ans == nullptr && (cur == o1 || cur == o2))
          {
            ans = cur;
          }
          mostRight->right = cur;
          cur = cur->left;
          continue;
        }
        else
        {
          mostRight->right = nullptr;
        }
      }
      else
      {
        if (ans == nullptr && (cur == o1 || cur == o2))
        {
          ans = cur;
        }
      }
      cur = cur->right;
    }
    return ans;
  }
};

void testLowestCommonAncestor()
{
  Solution s;
  TreeNode* r9 = new TreeNode(4, nullptr, nullptr);
  TreeNode* r8 = new TreeNode(7, nullptr, nullptr);
  TreeNode* r7 = new TreeNode(8, nullptr, nullptr);
  TreeNode* r6 = new TreeNode(0, nullptr, nullptr);
  TreeNode* r5 = new TreeNode(2, r8, r9);
  TreeNode* r4 = new TreeNode(6, nullptr, nullptr);
  TreeNode* r3 = new TreeNode(1, r6, r7);
  TreeNode* r2 = new TreeNode(5, r4, r5);
  TreeNode* r1 = new TreeNode(3, r2, r3);
  EXPECT_TRUE(r1 == s.lowestCommonAncestor1(r1, r2, r3));
  EXPECT_TRUE(r2 == s.lowestCommonAncestor1(r1, r2, r9));
  EXPECT_TRUE(r1 == s.lowestCommonAncestor2(r1, r2, r3));
  EXPECT_TRUE(r2 == s.lowestCommonAncestor2(r1, r2, r9));
  EXPECT_SUMMARY;
}

int main()
{
  testLowestCommonAncestor();
  return 0;
}
