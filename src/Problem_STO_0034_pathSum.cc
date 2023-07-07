#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

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
  void dfs(TreeNode *root, int target, vector<int> &path, vector<vector<int>> &ans)
  {
    if (root == nullptr)
    {
      return;
    }
    path.emplace_back(root->val);
    target -= root->val;
    if (root->left == nullptr && root->right == nullptr && target == 0)
    {
      ans.push_back(path);
    }
    dfs(root->left, target, path, ans);
    dfs(root->right, target, path, ans);
    path.pop_back();
  }

  // dfs
  vector<vector<int>> pathSum1(TreeNode *root, int target)
  {
    vector<vector<int>> ans;
    vector<int> path;
    dfs(root, target, path, ans);
    return ans;
  }

  // bfs
  vector<vector<int>> pathSum2(TreeNode *root, int target)
  {
    vector<vector<int>> ans;
    unordered_map<TreeNode *, TreeNode *> parents;

    if (root == nullptr)
    {
      return ans;
    }

    queue<std::pair<TreeNode *, int>> q;
    q.push({root, 0});

    auto getPath = [&](TreeNode *node)
    {
      vector<int> tmp;
      while (node != nullptr)
      {
        tmp.emplace_back(node->val);
        node = parents[node];
      }
      std::reverse(tmp.begin(), tmp.end());
      ans.push_back(tmp);
    };

    while (!q.empty())
    {
      auto [node, sum] = q.front();
      q.pop();
      int v = sum + node->val;

      if (node->left == nullptr && node->right == nullptr)
      {
        if (v == target)
        {
          getPath(node);
        }
      }
      else
      {
        if (node->left != nullptr)
        {
          parents[node->left] = node;
          q.push({node->left, v});
        }
        if (node->right != nullptr)
        {
          parents[node->right] = node;
          q.push({node->right, v});
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  TreeNode *x10 = new TreeNode(1, nullptr, nullptr);
  TreeNode *x9 = new TreeNode(5, nullptr, nullptr);
  TreeNode *x8 = new TreeNode(2, nullptr, nullptr);
  TreeNode *x7 = new TreeNode(7, nullptr, nullptr);
  TreeNode *x6 = new TreeNode(4, x9, x10);
  TreeNode *x5 = new TreeNode(13, nullptr, nullptr);
  TreeNode *x4 = new TreeNode(11, x7, x8);
  TreeNode *x3 = new TreeNode(8, x5, x6);
  TreeNode *x2 = new TreeNode(4, x4, nullptr);
  TreeNode *x1 = new TreeNode(5, x2, x3);

  TreeNode *y3 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y2 = new TreeNode(2, nullptr, nullptr);
  TreeNode *y1 = new TreeNode(1, y2, y3);

  TreeNode *z2 = new TreeNode(2, nullptr, nullptr);
  TreeNode *z1 = new TreeNode(1, z2, nullptr);

  vector<vector<int>> o1 = {{5, 4, 11, 2}, {5, 8, 4, 5}};
  vector<vector<int>> o2 = {};
  vector<vector<int>> o3 = {};

  EXPECT_TRUE(o1 == s.pathSum1(x1, 22));
  EXPECT_TRUE(o2 == s.pathSum1(y1, 5));
  EXPECT_TRUE(o3 == s.pathSum1(z1, 0));

  EXPECT_TRUE(o1 == s.pathSum2(x1, 22));
  EXPECT_TRUE(o2 == s.pathSum2(y1, 5));
  EXPECT_TRUE(o3 == s.pathSum2(z1, 0));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
