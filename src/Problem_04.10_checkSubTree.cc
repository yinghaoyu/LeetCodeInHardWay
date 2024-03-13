#include <iostream>

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
 private:
  // 检查两棵树是否一致
  bool check(TreeNode* t1, TreeNode* t2)
  {
    if (t1 == nullptr && t2 == nullptr)
    {
      return true;
    }
    if (t1 == nullptr || t2 == nullptr)
    {
      return false;
    }
    if (t1->val != t2->val)
    {
      return false;
    }
    return check(t1->left, t2->left) && check(t1->right, t2->right);
  }

 public:
  // 检查 t2 是否是 t1 的子树
  bool checkSubTree(TreeNode* t1, TreeNode* t2)
  {
    if (t1 == nullptr)
    {
      return false;
    }
    return check(t1, t2) || checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
  }
};
