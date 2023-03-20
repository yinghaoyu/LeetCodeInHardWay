#include <iostream>

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
  TreeNode *invertTree(TreeNode *root)
  {
    if (root == nullptr)
    {
      return nullptr;
    }
    //下面三句是将当前节点的左右子树交换
    TreeNode *tmp = root->right;
    root->right = root->left;
    root->left = tmp;
    //递归交换当前节点的 左子树
    invertTree(root->left);
    //递归交换当前节点的 右子树
    invertTree(root->right);
    //函数返回时就表示当前这个节点，以及它的左右子树
    //都已经交换完了
    return root;
  };
