#include <iostream>
#include <queue>
#include <unordered_map>
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

// seem as leetcode 0199
// https://leetcode-cn.com/problems/binary-tree-right-side-view/
// see at Problem_0199_rightSideView.cc
class Solution
{
 public:
  // dfs
  vector<int> rightSideView1(TreeNode *root)
  {
    if (root == nullptr)
    {
      return {};
    }
    unordered_map<int, int> map;
    int max_depth = -1;
    // 这里是栈
    vector<tuple<TreeNode *, int>> stack;
    stack.push_back({root, 0});
    while (!stack.empty())
    {
      // 注意这里不能用引用，因为 后面有 pop_back 导致引用失效
      // auto &[node, depth] = stack.back();
      auto [node, depth] = stack.back();
      stack.pop_back();
      // 更新最大深度
      max_depth = std::max(max_depth, depth);

      if (map.find(depth) == map.end())
      {
        // 第一次访问，记录节点值
        map.emplace(depth, node->val);
      }

      if (node->left)
      {
        stack.push_back({node->left, depth + 1});
      }
      // 因为 right 是最后进栈，那么优先出栈访问
      if (node->right)
      {
        stack.push_back({node->right, depth + 1});
      }
    }

    vector<int> ans;
    for (int i = 0; i <= max_depth; i++)
    {
      ans.push_back(map[i]);
    }
    return ans;
  }

  // bfs
  vector<int> rightSideView2(TreeNode *root)
  {
    if (root == nullptr)
    {
      return {};
    }
    unordered_map<int, int> map;
    int max_depth = -1;
    // 这里是队列
    queue<tuple<TreeNode *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
      // 注意这里不能用引用，因为 后面有 pop 会导致引用失效
      auto [node, depth] = q.front();
      q.pop();
      // 更新最大深度
      max_depth = std::max(max_depth, depth);

      // 由于每一层最后一个访问到的节点才是我们要的答案，因此不断更新对应深度的信息即可
      map[depth] = node->val;

      if (node->left)
      {
        q.push({node->left, depth + 1});
      }
      if (node->right)
      {
        q.push({node->right, depth + 1});
      }
    }

    vector<int> ans;
    for (int i = 0; i <= max_depth; i++)
    {
      ans.push_back(map[i]);
    }
    return ans;
  }
};
