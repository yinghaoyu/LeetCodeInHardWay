#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

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
  int dfs(TreeNode *cur, int sum)
  {
    if (cur == nullptr)
    {
      return 0;
    }
    sum = sum * 10 + cur->val;
    if (cur->left == nullptr && cur->right == nullptr)
    {
      return sum;
    }
    return dfs(cur->left, sum) + dfs(cur->right, sum);
  }

  int sumNumbers(TreeNode *root) { return dfs(root, 0); }

  int bfs(TreeNode *root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    int sum = 0;
    queue<tuple<TreeNode *, int>> q;
    q.push({root, root->val});
    while (!q.empty())
    {
      auto [node, num] = q.front();
      q.pop();
      if (node->left == nullptr && node->right == nullptr)
      {
        sum += num;
      }
      else
      {
        if (node->left != nullptr)
        {
          q.push({node->left, num * 10 + node->left->val});
        }
        if (node->right != nullptr)
        {
          q.push({node->right, num * 10 + node->right->val});
        }
      }
    }
    return sum;
  }
};
