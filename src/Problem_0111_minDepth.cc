#include <algorithm>
#include <cstdint>

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
  int minDepth1(TreeNode* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
      return 1;
    }
    int ans = INT32_MAX;
    if (root->left != nullptr)
    {
      ans = std::min(ans, minDepth1(root->left));
    }
    if (root->right != nullptr)
    {
      ans = std::min(ans, minDepth1(root->right));
    }
    return ans + 1;
  }

  // Morris
  int minDepth2(TreeNode* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    TreeNode* cur = root;
    TreeNode* mostRight = nullptr;
    // 上一个节点所在的层数
    int preLevel = 0;
    // 树的右边界长度
    int rightLen = 0;
    int ans = INT32_MAX;
    while (cur != nullptr)
    {
      mostRight = cur->left;
      if (mostRight != nullptr)
      {
        rightLen = 1;
        while (mostRight->right != nullptr && mostRight->right != cur)
        {
          rightLen++;
          mostRight = mostRight->right;
        }
        if (mostRight->right == nullptr)
        {
          preLevel++;
          mostRight->right = cur;
          cur = cur->left;
          continue;
        }
        else
        {
          if (mostRight->left == nullptr)
          {
            ans = std::min(ans, preLevel);
          }
          preLevel -= rightLen;
          mostRight->right = nullptr;
        }
      }
      else
      {
        preLevel++;
      }
      cur = cur->right;
    }
    // 不要忘了整棵树的最右节点
    rightLen = 1;
    cur = root;
    while (cur->right != nullptr)
    {
      rightLen++;
      cur = cur->right;
    }
    // 整棵树的最右节点是叶节点才纳入统计
    if (cur->left == nullptr)
    {
      ans = std::min(ans, rightLen);
    }
    return ans;
  }
};
