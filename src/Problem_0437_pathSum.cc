#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

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
  int pathSum(TreeNode* root, int targetSum)
  {
    unordered_map<long long, int> map;
    // 这是因为任何节点本身也可以形成一个路径（长度为1的路径）。
    // 如果某个节点的值就为target，那么它本身就是一个解。
    // 前缀和0正好可以与它形成这个解。
    // 对任何节点而言，本身就是解最多只能有一个，所以一开始empale(0, 1)。
    // 相当于给所有节点一个可单独形成合法路径的机会。
    map.emplace(0L, 1);
    return process(root, targetSum, 0, map);
  }

  // 前缀和
  int process(TreeNode* x, int targetSum, long long pre, unordered_map<long long, int>& map)
  {
    if (x == nullptr)
    {
      return 0;
    }
    long long all = pre + x->val;
    int ans = 0;
    if (map.count(all - targetSum))
    {
      // 说明路径上存在和为 targetSum
      ans = map.at(all - targetSum);
    }
    if (!map.count(all))
    {
      map.emplace(all, 1);
    }
    else
    {
      map[all]++;
    }
    ans += process(x->left, targetSum, all, map);
    ans += process(x->right, targetSum, all, map);
    // 回溯，保证map里的值一定是连续的节点生成的
    if (map.at(all) == 1)
    {
      map.erase(all);
    }
    else
    {
      map[all]--;
    }
    return ans;
  }
};

void testPathSum()
{
  Solution s;
  TreeNode* x9 = new TreeNode(1, nullptr, nullptr);
  TreeNode* x8 = new TreeNode(-2, nullptr, nullptr);
  TreeNode* x7 = new TreeNode(3, nullptr, nullptr);
  TreeNode* x6 = new TreeNode(11, nullptr, nullptr);
  TreeNode* x5 = new TreeNode(2, nullptr, x9);
  TreeNode* x4 = new TreeNode(3, x7, x8);
  TreeNode* x3 = new TreeNode(-3, nullptr, x6);
  TreeNode* x2 = new TreeNode(5, x4, x5);
  TreeNode* x1 = new TreeNode(10, x2, x3);
  EXPECT_EQ_INT(3, s.pathSum(x1, 8));
  EXPECT_SUMMARY;
}

int main()
{
  testPathSum();
  return 0;
}
