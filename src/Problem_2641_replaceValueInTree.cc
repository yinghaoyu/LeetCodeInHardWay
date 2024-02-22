#include <vector>

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
  // BFS
  TreeNode* replaceValueInTree(TreeNode* root)
  {
    vector<TreeNode*> qA = {root};
    // 根节点一定没有堂兄弟
    root->val = 0;
    while (!qA.empty())
    {
      vector<TreeNode*> qB;
      int sum = 0;
      // 先统计所有同层的节点和
      for (auto& cur : qA)
      {
        if (cur->left)
        {
          qB.push_back(cur->left);
          sum += cur->left->val;
        }
        if (cur->right)
        {
          qB.push_back(cur->right);
          sum += cur->right->val;
        }
      }
      // 再更新节点的值
      for (auto& cur : qA)
      {
        int child_sum = (cur->left ? cur->left->val : 0) + (cur->right ? cur->right->val : 0);
        if (cur->left)
        {
          cur->left->val = sum - child_sum;
        }
        if (cur->right)
        {
          cur->right->val = sum - child_sum;
        }
      }
      qA.swap(qB);
    }
    return root;
  }
};
