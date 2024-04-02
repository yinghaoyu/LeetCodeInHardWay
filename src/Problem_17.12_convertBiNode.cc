#include <vector>

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
  // 头结点
  TreeNode* head = nullptr;
  // 前驱结点
  TreeNode* pre = nullptr;

 public:
  // 利用中序遍历
  void f(TreeNode* cur)
  {
    if (cur == nullptr)
    {
      return;
    }
    f(cur->left);
    if (head == nullptr)
    {
      // 第一次遍历头
      head = cur;
    }
    else
    {
      // 让前驱节点的右边指向当前节点
      pre->right = cur;
    }
    // 更新前驱节点
    pre = cur;
    // 当前节点的左边清空
    cur->left = nullptr;
    f(cur->right);
  }

  TreeNode* convertBiNode(TreeNode* root)
  {
    f(root);
    return head;
  }
};
