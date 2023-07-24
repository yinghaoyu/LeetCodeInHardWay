#include <functional>
#include <iostream>
#include <queue>

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
  // bfs
  int findBottomLeftValue1(TreeNode *root)
  {
    queue<TreeNode *> q;
    q.push(root);
    int ans = root->val;
    while (!q.empty())
    {
      TreeNode *cur = q.front();
      q.pop();
      // 先让右孩子进队，后让左节点进队
      // 这样每层最后访问的节点是最左的子节点
      if (cur->right)
      {
        q.push(cur->right);
      }
      if (cur->left)
      {
        q.push(cur->left);
      }
      ans = cur->val;
    }
    return ans;
  }

  // dfs
  int findBottomLeftValue2(TreeNode *root)
  {
    int curValue;
    int curHeight;
    std::function<void(TreeNode *, int)> dfs = [&](TreeNode *cur, int height)
    {
      if (cur == nullptr)
      {
        return;
      }
      height++;
      // 递归先遍历左子树
      dfs(cur->left, height);
      dfs(cur->right, height);
      // 找到深度最深的左子节点
      if (height > curHeight)
      {
        curHeight = height;
        curValue = cur->val;
      }
    };

    dfs(root, 0);

    return curValue;
  }
};
