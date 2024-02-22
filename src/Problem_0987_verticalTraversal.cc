#include <algorithm>
#include <cstdint>
#include <tuple>
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
  void f(TreeNode* cur, int row, int column, vector<tuple<int, int, int>>& nodes)
  {
    if (cur == nullptr)
    {
      return;
    }
    nodes.emplace_back(column, row, cur->val);
    f(cur->left, row + 1, column - 1, nodes);
    f(cur->right, row + 1, column + 1, nodes);
  }

  vector<vector<int>> verticalTraversal(TreeNode* root)
  {
    // column row value
    vector<tuple<int, int, int>> nodes;
    // 遍历整棵树，生成坐标
    f(root, 0, 0, nodes);
    // 按关键字 column row value 分级排序
    std::sort(nodes.begin(), nodes.end());
    vector<vector<int>> ans;
    int lastcol = INT32_MIN;
    for (auto& [column, row, val] : nodes)
    {
      if (column != lastcol)
      {
        // 列号不同生成另一个数组保存新的列
        lastcol = column;
        ans.emplace_back();
      }
      ans.back().push_back(val);
    }
    return ans;
  }
};
