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

class Solution
{
 public:
  vector<int> rightSideView(TreeNode *root)
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
